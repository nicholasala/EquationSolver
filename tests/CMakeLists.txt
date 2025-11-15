add_executable(tests ../Unity/src/unity.h
    ../Unity/src/unity.c
    ../src/Tokenizer.c
    ../src/Interpreter.c
    ../src/model/Token.h
    ../src/model/TokenType.h
    TestTokenizer.c
    TestTokenizer.h
    main.c
    TestInterpreter.c
    TestInterpreter.h
)