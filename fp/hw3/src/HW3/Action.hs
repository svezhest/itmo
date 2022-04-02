{-# LANGUAGE InstanceSigs #-}

module HW3.Action
  ( HIO (..)
  , HiPermission (..)
  , PermissionException (..)
  ) where

import Control.Exception (Exception, throw)
import Data.Set (Set, member)
import GHC.IO.Exception (IOErrorType (PermissionDenied))
import qualified Data.ByteString as B
import qualified Data.Sequence as Q
import qualified Data.Text as T
import qualified System.Directory as D
import Data.Text.Encoding (decodeUtf8')
import System.Random (getStdRandom, uniformR)
import Data.Time.Clock (getCurrentTime)
import HW3.Base
import Control.Monad (liftM, ap)

data HiPermission =
    AllowRead
  | AllowWrite
  | AllowTime
  deriving (Show, Eq, Ord, Enum, Bounded)

data PermissionException =
  PermissionRequired HiPermission
  deriving Show

instance Exception PermissionException

newtype HIO a = HIO { runHIO :: Set HiPermission -> IO a }

instance Monad HIO where
  return :: a -> HIO a
  return x = HIO (\_ -> return x)

  (>>=) :: HIO a -> (a -> HIO b) -> HIO b
  m >>= f = HIO (\set -> do
    x <- runHIO m set
    runHIO (f x) set)
--
instance Functor HIO where
  fmap = liftM

instance Applicative HIO where
  pure = return
  (<*>) = ap

instance HiMonad HIO where
  runAction :: HiAction -> HIO HiValue
  runAction action = HIO (\permissions -> do
    case action of
      HiActionMkDir file ->
        if member AllowWrite permissions
          then do
            D.createDirectory file
            return HiValueNull
        else throw $ PermissionRequired AllowWrite

      HiActionRead file ->
        if member AllowRead permissions
          then do
            typeOfAction <- D.doesDirectoryExist file
            if typeOfAction
              then (HiValueList . Q.fromList . map (HiValueString . T.pack)) <$> D.getDirectoryContents file
            else (\bytes -> case decodeUtf8' bytes of
                Right utf8 -> HiValueString utf8
                Left _ -> HiValueBytes bytes) <$> B.readFile file
        else throw $ PermissionRequired AllowRead

      HiActionWrite file bytes ->
        if member AllowWrite permissions
          then do
            B.writeFile file bytes
            return HiValueNull
        else throw $ PermissionRequired AllowWrite

      HiActionChDir file ->
        if member AllowRead permissions
          then do
            D.setCurrentDirectory file
            return HiValueNull
        else throw $ PermissionRequired AllowRead

      HiActionCwd ->
        if member AllowRead permissions
          then (HiValueString . T.pack) <$> D.getCurrentDirectory
        else throw $ PermissionRequired AllowRead

      HiActionRand a b -> (HiValueNumber . toRational) <$> getStdRandom (uniformR (a, b))

      HiActionNow ->
        if member AllowTime permissions
          then HiValueTime <$> getCurrentTime
        else throw $ PermissionRequired AllowTime

      HiActionEcho str ->
        if member AllowWrite permissions
          then do
            putStrLn $ T.unpack str
            return HiValueNull
        else throw $ PermissionRequired AllowWrite
    )

