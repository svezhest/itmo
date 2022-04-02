module HW1.T7 where

data ListPlus a = a :+ ListPlus a | Last a deriving (Show)

infixr 5 :+

instance Semigroup (ListPlus a) where
  (<>) a b = case a of
    Last x -> x :+ b
    x :+ xs -> x :+ (xs <> b)

data Inclusive a b = This a | That b | Both a b deriving (Show)

instance (Semigroup a, Semigroup b) => Semigroup (Inclusive a b) where
  (<>) a b = case (a, b) of
    (This x, This y) -> This (x <> y)
    (This x, That y) -> Both x y
    (This x, Both y1 y2) -> Both (x <> y1) y2
    (That x, That y) -> That (x <> y)
    (That x, Both y1 y2) -> Both y1 (x <> y2)
    (Both x1 x2, Both y1 y2) -> Both (x1 <> y1) (x2 <> y2)
    _ -> b <> a

newtype DotString = DS String deriving Show

instance Semigroup DotString where
  (<>) (DS a) (DS b) = DS (helper a b)
    where
      helper x y
        | x == "" = y
        | y == "" = x
        | otherwise = x ++ "." ++ y

instance Monoid DotString where
  mempty = DS ""

newtype Fun a = F (a -> a)

apply :: Fun a -> a -> a
(F f) `apply` x = f x

instance Semigroup (Fun a) where
  (<>) (F f) (F g) = F (f . g)
 
instance Monoid (Fun a) where
  mempty = F id

