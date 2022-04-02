module HW1.T3 where

import Data.List (sort, nub)

data Tree a = Leaf | Branch {size :: Int, left :: Tree a, value :: a, right :: Tree a} deriving (Show)

mkBranch :: Ord a => Tree a -> a -> Tree a -> Tree a
mkBranch Leaf x Leaf = Branch 1 Leaf x Leaf
mkBranch Leaf x r
  | x < y = Branch sz Leaf x r
  | x > y = Branch sz r x Leaf
  | x == y = r
  where
    y = value r; sz = size r + 1
mkBranch l x Leaf
  | y < x = Branch sz l x Leaf
  | y > x = Branch sz Leaf x l
  | y == x = l
  where
    y = value l; sz = size l + 1
mkBranch l x r
  | length vals == 2 = mergeBranches (l {value = head vals}) (r {value = vals !! 1})
  | length vals == 3 = refreshSize (Branch 0 (mkBranch (left l) (head vals) (right l)) (vals !! 1) (mkBranch (left r) (vals !! 2) (right r)))
  where
    vals = sort $ nub [value l, x, value r]

refreshSize :: Tree a -> Tree a
refreshSize t = t {size = tsize (left t) + 1 + tsize (right t)}

mergeBranches :: Ord a => Tree a -> Tree a -> Tree a
mergeBranches x Leaf = x
mergeBranches Leaf x = x
mergeBranches l r
  | size l > size r = mergeBranches r l
  | value l > value r = refreshSize (r {right = mergeBranches l (right r)})
  | value l < value r = refreshSize (r {left = mergeBranches l (left r)})
  | value l == value r = mkBranch (mergeBranches (left l) (left r)) (value l) (mergeBranches (right l) (right r))

-- | Size of the tree, O(1).
tsize :: Tree a -> Int
tsize Leaf = 0
tsize x = size x

-- | Depth of the tree.
tdepth :: Tree a -> Int
tdepth Leaf = 0
tdepth x = 1 + max (tdepth (left x)) (tdepth (right x))

-- | Check if the element is in the tree, O(log n)
tmember :: Ord a => a -> Tree a -> Bool
tmember _ Leaf = False
tmember x t
  | value t == x = True
  | otherwise = tmember x (left t) || tmember x (right t)

-- | Insert an element into the tree, O(log n)
tinsert :: Ord a => a -> Tree a -> Tree a
tinsert x t = mergeBranches t (mkBranch Leaf x Leaf)

-- | Build a tree from a list, O(n log n)
tFromList :: Ord a => [a] -> Tree a
tFromList = foldr tinsert Leaf
