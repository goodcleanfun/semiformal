[ ]+              { return TOKEN_TYPE_WHITESPACE; }
[a-zA-Z]+         { return TOKEN_TYPE_WORD; }
*                 { return TOKEN_TYPE_OTHER; }
