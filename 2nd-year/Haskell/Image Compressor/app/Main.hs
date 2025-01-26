{-
-- EPITECH PROJECT, 2024
-- B-FUN-400-STG-4-1-compressor-nahim.kandari
-- File description:
-- Main
-}

module Main (main) where

import Options.Applicative
import Control.Exception (try, IOException)
import System.IO (openFile, hGetContents, hClose, IOMode(ReadMode), Handle)
import System.Exit (exitWith, ExitCode(..), exitSuccess)
import Parsing
import Includes
import Algorithme

instance Show Point where
  show point = show (position point) ++ " " ++ show (color point)

instance Show Color where
  show (Color (r, g, b)) =
    "(" ++ show r ++ "," ++ show g ++ "," ++ show b ++ ")"

instance Show Position where
  show (Position (x, y)) = "(" ++ show x ++ "," ++ show y ++ ")"

run :: [Point] -> Int -> Float -> IO ()
run pts nn ll  = do
  colors <- launchAlgo pts nn ll
  displayResult pts colors

useArgs :: Vectors -> IO ()
useArgs (Vectors nn ll ff) = do
    file <- try (openFile ff ReadMode) :: IO (Either IOException Handle)
    case file of
        Left exception -> exitWith (ExitFailure 84)
        Right file -> do
            content <- hGetContents file
            let pts = parseFile content
            if null pts || content == "" then exitWith (ExitFailure 84) else
                run pts nn ll
            hClose file

displayResult :: [Point] -> [Color] -> IO ()
displayResult points colors = mapM_ (\(cluster, centroid) -> putStrLn ("--\n"
  ++ show centroid ++ "\n-")
  >> mapM_ print cluster) (zip (sortFunc points colors) colors)

main :: IO ()
main = do
  result <- try (execParser opts) :: IO (Either ExitCode Vectors)
  case result of
    Left exeption -> exitWith (ExitFailure 84)
    Right vectors -> useArgs vectors
  where
    opts = info (parseArgs <**> helper)
      ( fullDesc
     <> progDesc "Parse tuples"
     <> header "tuple parser - a test for optparse-applicative" )