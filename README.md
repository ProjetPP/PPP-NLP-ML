PPP-QuestionParsing-ML-Reformulation
====================================

[![Build Status](https://travis-ci.org/ProjetPP/PPP-QuestionParsing-ML-Reformulation.svg?branch=master)](https://travis-ci.org/ProjetPP/PPP-QuestionParsing-ML-Reformulation)

## use this package
1. build with cmake : cmake then make reformulation
2. `wget https://github.com/Attempto/Clex/blob/master/clex_lexicon.pl?raw=true`
3. use python3: prepare environment
  ```
    import libreformulation
    libreformulation.load()
  ```
4. reformule request :
  `libreformulation.reformule('(subject,predicate,object)')`
