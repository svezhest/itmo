module HW0.T4 where

import Data.Function (fix)
import Numeric.Natural (Natural)

repeat' :: a -> [a]             -- behaves like Data.List.repeat
repeat' x = fix (x:)

map' :: (a -> b) -> [a] -> [b]  -- behaves like Data.List.map
map' f = fix helper where
  helper _ [] = []
  helper helper' (x:xs) = (f x) : (helper' xs)

fib :: Natural -> Natural       -- computes the n-th Fibonacci number
fib = fix helper 0 1 where
  helper _ a _ 0 = a
  helper helper' a b n = helper' b (a + b) (n - 1)

fac :: Natural -> Natural       -- computes the factorial
fac = fix helper where
  helper _ 0 = 1
  helper helper' n = n * helper' (n - 1)