import HW3.Base
import HW3.Evaluator
import HW3.Parser
import HW3.Pretty
import Data.Set(fromList)
import HW3.Action
import System.Console.Haskeline
import Control.Monad.IO.Class (liftIO)

main :: IO ()
main = runInputT defaultSettings loop
  where
    loop :: InputT IO ()
    loop = do
      minput <- getInputLine "hi> "
      case minput of
        Nothing -> return ()
        Just "quit" -> return ()
        Just input -> do
          case parse input of
            Left e -> do outputStrLn (show e)
            Right expression -> do
              line <- liftIO $ runHIO (eval expression) (fromList [AllowRead, AllowWrite, AllowTime])
              case line of
               Left e -> do outputStrLn (show e)
               Right val -> do outputStrLn (show (prettyValue val))
          loop