module HW1.T5 where

import Data.List.NonEmpty

splitOn :: Eq a => a -> [a] -> NonEmpty [a]
splitOn _ [] = [] :| []
splitOn sep xs
  | null after = before :| []
  | otherwise = before :| toList (splitOn sep $ Prelude.drop 1 after)
  where
    before = Prelude.takeWhile (/= sep) xs
    after = Prelude.dropWhile (/= sep) xs

joinWith :: a -> NonEmpty [a] -> [a]
joinWith sep xs = Prelude.drop 1 $ foldl (\x y -> x ++ (sep : y)) [] xs
