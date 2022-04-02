module HW1.T1 where

import Numeric.Natural

data Day = Monday | Tuesday | Wednesday | Thursday | Friday | Saturday | Sunday deriving (Show)

intToDay :: Integral a => a -> Day
intToDay x = helper (x `mod` 7)
  where
    helper 0 = Monday
    helper 1 = Tuesday
    helper 2 = Wednesday
    helper 3 = Thursday
    helper 4 = Friday
    helper 5 = Saturday
    helper _ = Sunday

dayToInt :: Num p => Day -> p
dayToInt Monday = 0
dayToInt Tuesday = 1
dayToInt Wednesday = 2
dayToInt Thursday = 3
dayToInt Friday = 4
dayToInt Saturday = 5
dayToInt Sunday = 6

-- | Returns the day that follows the day of the week given as input.
nextDay :: Day -> Day
nextDay = afterDays 1

-- | Returns the day of the week after a given number of days has passed.
afterDays :: Natural -> Day -> Day
afterDays n = intToDay . (+ n) . dayToInt

-- | Checks if the day is on the weekend.
isWeekend :: Day -> Bool
isWeekend Saturday = True
isWeekend Sunday = True
isWeekend _ = False

-- | Computes the number of days until the next Friday.
daysToParty :: Day -> Natural
daysToParty = (`mod` 7) . (11 -) . dayToInt
