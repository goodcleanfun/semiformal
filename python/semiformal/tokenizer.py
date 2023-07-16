from typing import List, Tuple

from semiformal import _tokenizer
from semiformal.token_types import TokenType

def tokens(text: str) -> Tuple[Tuple[int, int, int]]:
    return _tokenizer.tokens(text)


def tokenize(text: str, exclude_token_types: List[[TokenType, int]]=None) -> List[Tuple[str, TokenType]]:
    token_classes = [(s, TokenType(c)) for s, c in _tokenizer.tokenize(text)]

    if exclude_token_types:
        exclude_token_types = list(map(TokenType, exclude_token_types))
        token_classes = [(s, c) for s, c in token_classes if c not in exclude_token_types]

    return token_classes
