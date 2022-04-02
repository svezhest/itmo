module HW0.T5 where

import Numeric.Natural (Natural)

type Nat a = (a -> a) -> a -> a

nz :: Nat a
nz _ = id

ns :: Nat a -> Nat a
ns x f z = f (x f z)

nplus :: Nat a -> Nat a -> Nat a
nplus x y f z = x f (y f z)

nmult :: Nat a -> Nat a -> Nat a
nmult x y f z = x (y f) z

nFromNatural :: Natural -> Nat a
nFromNatural n
  | n == 0 = nz
  | otherwise = ns $ nFromNatural (n - 1)

nToNum :: Num a => Nat a -> a
nToNum nat = nat (+ 1) 0
