{-
-- EPITECH PROJECT, 2024
-- B-FUN-400-STG-4-1-compressor-nahim.kandari
-- File description:
-- Includes
-}

module Includes (Point(..),
                Color(..),
                Position(..),
                Vectors(..),
                BadPoint(..),
                TheFile(..)
                ) where

data Vectors = Vectors {
    n :: Int,
    l :: Float,
    f :: String
} deriving Show

newtype Position = Position (Int, Int)

newtype Color = Color (Int, Int, Int)

data BadPoint = BadPoint
    deriving Show

type TheFile = Either BadPoint Point -- TheFile prend soit la valeur de BadPoint soit la valeur de Point

data Point = Point {
    position :: Position,
    color :: Color
}
