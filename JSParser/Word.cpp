#include"Word.h"
#include"Tag.h"

Word* Word::And = new Word("&&", AND);
Word* Word::Or = new Word("||", OR);
Word* Word::Eq = new Word("==", EQ);
Word* Word::Ne = new Word("!=", NE);
Word* Word::Le = new Word("<=", LE);
Word* Word::Ge = new Word(">=", GE);
