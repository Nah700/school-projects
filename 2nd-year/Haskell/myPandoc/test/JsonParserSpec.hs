{-
-- EPITECH PROJECT, 2024
-- B-FUN-400-STG-4-1-mypandoc-noe.tritsch
-- File description:
-- JsonParserSpec
-}

module JsonParserSpec (spec) where

import Test.Hspec ( describe, it, shouldBe, Spec )
import JsonParser
    ( parseArray,
      parseJsonString,
      parseJsonValue,
      parseObject,
      parseString,
      JsonValue(JsonString, JsonArray, JsonObject) )
import ParserData ( Parser(runParser) )

spec :: Spec
spec = do
    describe "parseString" $ do
        it "should parse a simple string" $
            runParser parseString "\"hello\"" `shouldBe` Right ("hello", "")

        it "should parse a string with escaped characters" $
            runParser parseString "\"hello\\\"world\"" `shouldBe` Right ("hello\"world", "")

    describe "parseJsonString" $ do
        it "should parse a JsonString" $
            runParser parseJsonString "\"hello\"" `shouldBe` Right (JsonString "hello", "")

        it "should parse a JsonString with escaped characters" $
            runParser parseJsonString "\"hello\\\"world\"" `shouldBe` Right (JsonString "hello\"world", "")

    describe "parseArray" $ do
        it "should parse an empty array" $
            runParser parseArray "[]" `shouldBe` Right (JsonArray [], "")

        it "should parse an array with single element" $
            runParser parseArray "[\"hello\"]" `shouldBe` Right (JsonArray [JsonString "hello"], "")

        it "should parse an array with multiple elements" $
            runParser parseArray "[\"hello\", \"world\"]" `shouldBe` Right (JsonArray [JsonString "hello", JsonString "world"], "")

    describe "parseObject" $ do
        it "should parse an empty object" $
            runParser parseObject "{}" `shouldBe` Right (JsonObject [], "")

        it "should parse an object with single key-value pair" $
            runParser parseObject "{\"key\": \"value\"}" `shouldBe` Right (JsonObject [("key", JsonString "value")], "")

        it "should parse an object with multiple key-value pairs" $
            runParser parseObject "{\"key1\": \"value1\", \"key2\": \"value2\"}" `shouldBe` Right (JsonObject [("key1", JsonString "value1"), ("key2", JsonString "value2")], "")

    describe "parseJsonValue" $ do
        it "should parse a JsonString" $
            runParser parseJsonValue "\"hello\"" `shouldBe` Right (JsonString "hello", "")

        it "should parse a JsonArray" $
            runParser parseJsonValue "[\"hello\", \"world\"]" `shouldBe` Right (JsonArray [JsonString "hello", JsonString "world"], "")

        it "should parse a JsonObject" $
            runParser parseJsonValue "{\"key\": \"value\"}" `shouldBe` Right (JsonObject [("key", JsonString "value")], "")
