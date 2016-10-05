#pragma once
#include <vector>
#include <deque>
#include <string>

#include "FileReader.h"
#include "Automatan.h"
#include "Token.h"

#include "Comma.h"
#include "Period.h"
#include "Q_mark.h"
#include "Left_paren.h"
#include "Right_paren.h"
#include "Colon.h"
#include "ColonDash.h"
#include "Multiply.h"
#include "Add.h"
#include "Schemes.h"
#include "Facts.h"
#include "Rules.h"
#include "Queries.h"
#include "Id.h"
#include "String.h"
#include "Comment.h"
#include "Undefined_String.h"
#include "Undefined_Comment.h"
#include "Undefined.h"


class Scanner
{
public:
	Scanner();
	~Scanner();
	std::deque<Token*> read(FileReader input);
private:
	Token* generateToken(Automatan* a, FileReader input, int size);
};

