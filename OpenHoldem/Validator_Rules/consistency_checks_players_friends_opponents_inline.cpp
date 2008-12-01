BEGIN_TESTCASE
    TESTCASE_ID ("1400")
    HEURISTIC_RULE (false)
    REASONING ("The sets of friends and opponents have to be disjoint.")
    PRECONDITION (true)
    POSTCONDITION ((int(gws("nopponentsseatedbits")) & int(gws("nfriendsseatedbits"))) == 0)
    SYMBOLS_POSSIBLY_AFFECTED ("nopponentsseatedbits, nfriendsseatedbits")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("1401")
    HEURISTIC_RULE (false)
    REASONING ("All players dealt must be active")
    PRECONDITION (true)
    POSTCONDITION ((int(gws("playersdealtbits")) & int(gws("playersactivebits"))) == int(gws("playersdealtbits")))
    SYMBOLS_POSSIBLY_AFFECTED ("playersdealtbits, playersactivebits")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("1402")
    HEURISTIC_RULE (false)
    REASONING ("All players playing must be seated and dealt and active.")
    PRECONDITION (true)
    POSTCONDITION ((int(gws("playersplayingbits")) & int(gws("playersseatedbits")) & int(gws("playersdealtbits")) & int(gws("playersactivebits"))) == int(gws("playersplayingbits")))
    SYMBOLS_POSSIBLY_AFFECTED ("playersplayingbits, playersseatedbits, playersdealtbits, playersactivebits")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("1403")
    HEURISTIC_RULE (false)
    REASONING ("If buttons are visible (it's my turn), there must be at least 1 opponent playing.")
    PRECONDITION (gws("ismyturn"))
    POSTCONDITION ((int(gws("nopponentsplayingbits")) != 0) && (int(gws("nopponentsplaying") > 0)))
    SYMBOLS_POSSIBLY_AFFECTED ("ismyturn, nopponentsplayingbits, nopponentsplaying")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("1404")
    HEURISTIC_RULE (false)
    REASONING ("If there's a game going on (check for common cards, if I'm not at the table), then there must be at least 2 players playing.")
    PRECONDITION ((gws("$$cc0") != CARD_UNKNOWN) && (gws("$$cc0") != CARDBACK))
    POSTCONDITION (gws("nplayersplaying") >= 2)
    SYMBOLS_POSSIBLY_AFFECTED ("$$cc0, nplayersplaying")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("1405")
    HEURISTIC_RULE (false)
    REASONING ("If I hold cards, there must be at least 1 opponent playing.")
    PRECONDITION ((gws("$$pc0") != CARD_UNKNOWN) && (gws("$$pc0") != CARDBACK) && (gws("$$pc1") != CARD_UNKNOWN) && (gws("$$pc1") != CARDBACK))
    POSTCONDITION (gws("nopponentsplaying") >= 1)
    SYMBOLS_POSSIBLY_AFFECTED ("$$pc0, $$pc1, nopponentsplaying")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("1406")
    HEURISTIC_RULE (false)
    REASONING ("The number of players who are playing plus the ones who have folded must equal the number of players who got dealt cards. ")
    PRECONDITION (true)
    POSTCONDITION ((gws("nopponentsfolded") + gws("nopponentsplaying")) == gws("nopponentsplaying"))
    SYMBOLS_POSSIBLY_AFFECTED ("nopponentsfolded, nopponentsplaying, nopponentsplaying")
END_TESTCASE


BEGIN_TESTCASE
    TESTCASE_ID ("1407")
    HEURISTIC_RULE (false)
    REASONING ("The sets of players playing, folded and sitting out are disjoint.")
    PRECONDITION (true)
    POSTCONDITION (((int(gws("opponentssplayingbits")) & int(gws("opponentsfoldedbits"))) == 0) && ((int(gws("playersplayingbits")) & !int(gws("playersactivebits"))) == 0) && ((int(gws("opponentsfoldedbits")) & !int(gws("playersactivebits"))) == 0))
    SYMBOLS_POSSIBLY_AFFECTED ("opponentssplayingbits, opponentsfoldedbits, playersplayingbits, playersactivebits")
END_TESTCASE