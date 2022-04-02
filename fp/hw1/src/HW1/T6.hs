module HW1.T6 where

mcat :: Monoid a => [Maybe a] -> a
mcat [] = mempty
mcat (x : xs) = case x of
  Nothing -> mcat xs
  Just a -> a <> mcat xs

epart :: (Monoid a, Monoid b) => [Either a b] -> (a, b)
epart [] = (mempty, mempty)
epart (x : xs) = case x of 
  Left l -> (l <> resl, resr)
  Right r -> (resl, r <> resr)
  where (resl, resr) = epart xs