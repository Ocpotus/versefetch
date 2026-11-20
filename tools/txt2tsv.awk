#!/usr/bin/awk -f
# Converts the Project Gutenberg Douay-Rheims text (assets/bible.txt) into a
# tab-separated file with one verse per line:
#
#   testament <TAB> book <TAB> chapter <TAB> verse <TAB> text
#
# Usage: awk -f tools/txt2tsv.awk assets/bible.txt > assets/bible.tsv
#
# Commentary paragraphs and chapter summaries are dropped: only lines that
# start with "C:V." (and their continuation lines) are kept.

# Print one verse. Fixes Psalms 9 and 113, whose second half restarts at
# verse 1 in the source; they are renumbered to the traditional 9:22-39 and
# 113:9-26.
function emit(c, v, t) {
	if (book SUBSEP c == lastchap && v == 1 && lastverse > 1)
		offset = lastverse
	else if (book SUBSEP c != lastchap)
		offset = 0
	lastchap = book SUBSEP c
	lastverse = v + offset
	printf "%s\t%s\t%d\t%d\t%s\n", testament, book, c, lastverse, t
}

# Emit the buffered verse. Some source lines contain two verses run
# together ("...commanded.  7:23. And he..."), so split those out.
# Only split when the embedded reference is the next verse of the same
# chapter, so stray references inside the text are left alone.
function flush(    head, rest, ref, r) {
	if (text == "")
		return
	rest = text
	head = ""
	while (match(rest, / +[0-9]+:[0-9]+\. /)) {
		ref = substr(rest, RSTART, RLENGTH)
		gsub(/[ .]/, "", ref)
		split(ref, r, ":")
		if (r[1] == chap && r[2] == verse + 1) {
			emit(chap, verse, head substr(rest, 1, RSTART - 1))
			verse = r[2]
			head = ""
		} else {
			head = head substr(rest, 1, RSTART + RLENGTH - 1)
		}
		rest = substr(rest, RSTART + RLENGTH)
	}
	emit(chap, verse, head rest)
	text = ""
}

BEGIN { testament = "OT" }

{ sub(/\r$/, "") }

/^THE NEW TESTAMENT$/ && book != "" { flush(); testament = "NT"; next }

# "Genesis Chapter 1", "1 Kings Chapter 3", "Canticle of Canticles Chapter 2"
/^[1-4]?[ ]?[A-Z][a-z]+( of [A-Z][a-z]+)? Chapter [0-9]+$/ {
	flush()
	book = $0
	sub(/ Chapter [0-9]+$/, "", book)
	next
}

# Start of a verse: "3:16. For God so loved...". The source occasionally
# has "3:16:" or "3:16" instead, so accept those too.
book != "" && /^[0-9]+:[0-9]+[.:]? / {
	flush()
	split($1, ref, /[:.]/)
	chap = ref[1]; verse = ref[2]
	text = $0
	sub(/^[0-9]+:[0-9]+[.:]? +/, "", text)
	next
}

# Blank line ends the verse; anything else while in a verse continues it.
/^[ \t]*$/ { flush(); next }
text != "" { gsub(/\t/, " "); text = text " " $0 }

END { flush() }
