module HW1.T2 where

import Numeric.Natural

data N = Z | S N deriving (Show)

nplus :: N -> N -> N -- addition
nplus Z b = b
nplus (S a) b = S (nplus a b)

nmult :: N -> N -> N -- multiplication
nmult Z _ = Z
nmult _ Z = Z
nmult (S a) b = nplus (nmult a b) b

nsub :: N -> N -> Maybe N -- subtraction     (Nothing if result is negative)
nsub Z Z = Just Z
nsub Z _ = Nothing
nsub a Z = Just a
nsub (S a) (S b) = nsub a b

ncmp :: N -> N -> Ordering -- comparison      (Do not derive Ord)
ncmp Z Z = EQ
ncmp Z _ = LT
ncmp _ Z = GT
ncmp (S a) (S b) = ncmp a b

nFromNatural :: Natural -> N
nFromNatural 0 = Z
nFromNatural n = S (nFromNatural (n - 1))

nToNum :: Num a => N -> a
nToNum Z = 0
nToNum (S x) = 1 + nToNum x

-- advanced plugs
-- for tests only
nEven :: N -> Bool
nEven = even . nToNum

nOdd :: N -> Bool
nOdd = odd . nToNum

ndiv :: N -> N -> N
ndiv a b = nFromNatural (nToNum a `div` nToNum b)

nmod :: N -> N -> N
nmod a b = nFromNatural (nToNum a `mod` nToNum b)
