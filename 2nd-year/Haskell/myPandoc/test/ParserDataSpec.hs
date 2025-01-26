{-
-- EPITECH PROJECT, 2024
-- B-FUN-400-STG-4-1-mypandoc-noe.tritsch
-- File description:
-- ParserDataSpec
-}

module ParserDataSpec (spec) where

import Test.Hspec ( Spec, describe, it, shouldBe, shouldSatisfy )
import ParserData
    ( Parser(runParser),
      parseAnd,
      parseAnyChar,
      parseChar,
      parseDouble,
      parseInt,
      parseMany,
      parseOr,
      parseSome,
      parseTruple,
      parseTuple,
      parseUInt,
      someone )

spec :: Spec
spec = do
    describe "parseChar" $ do
        it "should parse a specific character" $
            runParser (parseChar 'a') "abc" `shouldBe` Right ('a', "bc")

        it "should fail if the character is not found" $
            runParser (parseChar 'a') "xyz" `shouldSatisfy` isLeft

    describe "parseAnyChar" $ do
        it "should parse any character from a given list" $
            runParser (parseAnyChar "abc") "bac" `shouldBe` Right ('b', "ac")

        it "should fail if none of the characters are found" $
            runParser (parseAnyChar "abc") "xyz" `shouldSatisfy` isLeft

    describe "parseOr" $ do
        it "should parse the first parser if it succeeds" $
            runParser (parseOr (parseChar 'a') (parseChar 'b')) "abc" `shouldBe` Right ('a', "bc")

        it "should parse the second parser if the first one fails" $
            runParser (parseOr (parseChar 'x') (parseChar 'y')) "yz" `shouldBe` Right ('y', "z")

        it "should fail if both parsers fail" $
            runParser (parseOr (parseChar 'x') (parseChar 'y')) "abc" `shouldSatisfy` isLeft

    describe "parseAnd" $ do
        it "should parse two values in sequence" $
            runParser (parseAnd (parseChar 'a') (parseChar 'b')) "abc" `shouldBe` Right (('a', 'b'), "c")

    describe "parseMany" $ do
        it "should parse zero or more occurrences of a parser" $
            runParser (parseMany (parseChar 'a')) "aab" `shouldBe` Right ("aa", "b")

    describe "parseSome" $ do
        it "should parse one or more occurrences of a parser" $
            runParser (parseSome (parseChar 'a')) "aab" `shouldBe` Right ("aa", "b")

    describe "parseUInt" $ do
        it "should parse an unsigned integer" $
            runParser parseUInt "123abc" `shouldBe` Right (123, "abc")

    describe "parseInt" $ do
        it "should parse a signed integer" $
            runParser parseInt "-456abc" `shouldBe` Right (-456, "abc")

    describe "parseDouble" $ do
        it "should parse a double" $
            runParser parseDouble "3.14abc" `shouldBe` Right (3.14, "abc")

    describe "parseTuple" $ do
        it "should parse a tuple" $
            runParser (parseTuple parseInt) "(1,2)abc" `shouldBe` Right ((1, 2), "abc")

    describe "parseTruple" $ do
        it "should parse a triple tuple" $
            runParser parseTruple "(1,2,3)abc" `shouldBe` Right ((1, 2, 3), "abc")

    describe "someone" $ do
        it "should parse one or more occurrences of a parser" $
            runParser (someone (parseChar 'a')) "aab" `shouldBe` Right ("aa", "b")

isLeft :: Either a b -> Bool
isLeft (Left _) = True
isLeft _ = False
