#include "chunk.h"
#include "scanner.h"

void initScanner(Scanner* scanner, InputBuffer* inputBuffer) {
  scanner->start = inputBuffer->buffer;
  scanner->current = inputBuffer->buffer;
  scanner->inputBuffer = inputBuffer;
}

bool isAtEnd(Scanner* scanner) {
  return *(scanner->current) == '\0';
}

void skipWhitespace(Scanner* scanner) {
  while(*(scanner->current) == ' ') {
    scanner->current++;
  }
  scanner->start=scanner->current;
}

Token makeToken(Scanner* scanner, TokenType type) {
  Token token;
  token.start = scanner->start;
  token.length = (int)(scanner->current - scanner->start);
  token.type = type;
  return token;
}

bool isAlpha(char c) {
  return (c >= 'a' && c <= 'z') ||
         (c >= 'A' && c <= 'Z');
}

bool isKeyword(Scanner* scanner, char* keyword, int keywordLength) {
  int length = (int)(scanner->current - scanner->start);
  return length == keywordLength && (strncmp(scanner->start, keyword, length)==0);
}

char peek(Scanner* scanner) {
  return *(scanner->current);
}

char advance(Scanner* scanner) {
  scanner->current++;
  return scanner->current[-1];
}

Token makeIdentifier(Scanner* scanner) {
  while(isAlpha(peek(scanner))) advance(scanner);
  if (isKeyword(scanner, ".exit", 5)) return makeToken(scanner, TOKEN_EXIT);
  if (isKeyword(scanner, ".tables", 7)) return makeToken(scanner, TOKEN_TABLES);
  if (isKeyword(scanner, "insert", 6)) return makeToken(scanner, TOKEN_INSERT);
  if (isKeyword(scanner, "select", 6)) return makeToken(scanner, TOKEN_SELECT);
  
  return makeToken(scanner, TOKEN_IDENTIFIER);
}

Status runScanner(Scanner* scanner, Chunk* chunk) {
  skipWhitespace(scanner);

  for(;;) {
    if(isAtEnd(scanner)) {
      writeChunk(chunk, makeToken(scanner, TOKEN_EOF));
    }
    char c = advance(scanner);
    
    if (isAlpha(c) || c == '.') {
      writeChunk(chunk, makeIdentifier(scanner));
    } else if (c == ' ') {
      skipWhitespace(scanner);
    } else {
      return STATUS_SCAN_UNRECOGNIZED_CHARACTER;
    }
  }
  return STATUS_SCAN_SUCCESS;
}
