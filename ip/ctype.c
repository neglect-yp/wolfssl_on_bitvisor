int toupper(int c)
{
    char ch = (char)c;

    if ('a' <= ch && ch <= 'z')
        ch = ch - 'a' + 'A';

    return (int)ch;
}

int tolower(int c)
{
    char ch = (char)c;
    
    if ('A' <= ch && ch <= 'Z')
        ch = ch - 'A' + 'a';

    return (int)ch;
}
