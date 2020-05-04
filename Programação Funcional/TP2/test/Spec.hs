{-# LANGUAGE TupleSections #-}

import Small
import Data.Char
import Test.Tasty
import Test.Tasty.QuickCheck as QC
import Test.QuickCheck


-- generating valid names

genName :: Gen Name
genName = Name <$> vectorOf 5 (suchThat arbitrary isLetter)

instance Arbitrary Name where
  arbitrary = genName

genNames :: Gen [Name]
genNames
  = do
     n <- choose (3,10)
     vectorOf n genName


-- generating valid memory configurations

genPositive :: Gen Int
genPositive
  = suchThat arbitrary (\ x -> x >= 0 && x <= 20)

genMemory :: Gen [(Name,Int)]
genMemory
  = mapM (\ n -> (n,) <$> genPositive) =<< genNames

-- creates a valid stack with, at least, 5 itens.

genValidStack :: Gen [Int]
genValidStack
  = vectorOf 5 (suchThat arbitrary (\ x -> x > 0 && x <= 10))

-- generating arbitrary memory states

instance Arbitrary VMState where
  arbitrary = VMState 0 <$> genValidStack <*> genMemory


-- generating random programs

instance Arbitrary Instr where
  arbitrary
    = frequency
         [
           (20, IPush <$> genPositive)
         , (20, IVar  <$> genName)
         , (10, ISet  <$> genName)
         , (20, pure IAdd)
         , (20, pure ISub)
         , (10, IJump <$> genPositive)
         , (10, IJumpEq <$> genPositive)
         , (10, IJumpNeq <$> genPositive)
         ]


-- property one: push increases stack size

pushCorrect :: Int -> VMState -> Bool
pushCorrect n st
  = 1 + length (stack st) == length (stack (push n st))

-- property two: lookmemory should find a value, when it is
-- in memory and fail otherwise

pop :: [Int] -> Maybe Int
pop [] = Nothing
pop (x : _) = Just x

lookMemoryCorrect :: Name -> VMState -> Bool
lookMemoryCorrect n st
  = case lookup n (memory st) of
      Just v  -> pop (stack (lookMemory n st)) == Just v
      Nothing -> (0 : stack st) == (stack (lookMemory n st))

-- property three: set memory should modify the stack properly

setMemoryCorrect :: Name -> VMState -> Bool
setMemoryCorrect n st
  = case pop (stack st) of
      Nothing -> ((n,0) : memory st) == memory (setMemory n st)
      Just v  -> ((n,v) : memory st) == memory (setMemory n st)


-- property four: stackOp applies the correct operation on the stack

popTwo :: [Int] -> Maybe (Int,Int)
popTwo (x : y : _) = Just (x,y)
popTwo _ = Nothing

stackOpCorrect :: VMState -> Bool
stackOpCorrect st 
  = case popTwo (stack st) of
      Just (x,y) -> (x + y : tail (tail $ stack st) == stack (stackOp (+) st)) ||
                    (x - y : tail (tail $ stack st) == stack (stackOp (-) st))
      Nothing    -> (stack st == stack (stackOp (+) st)) ||
                    (stack st == stack (stackOp (-) st))

-- property five: checking the implementation of addPC

addPCCorrect :: Int -> VMState -> Bool
addPCCorrect n st
  = n + pc st == pc (addPC n st)

-- property six: checking conditional jump

condJumpCorrect :: (Int -> Int -> Bool) -> Int -> VMState -> Bool
condJumpCorrect op n st@(VMState p stk _)
  = case stk of
      (x : y : _) ->
        pc (condJump op n st) == if op x y then n + p else p + 1
      _           -> pc (condJump op n st) == p + 1

-- property seven: checking the implementation of vmStep

validPC :: VMState -> VMState -> Bool
validPC st st1 = 1 + pc st == pc st1

vmStepCorrect :: Instr -> VMState -> Bool
vmStepCorrect (IPush n) st
  = pushCorrect n st && validPC st (addPC 1 (push n st))
vmStepCorrect (IVar v) st
  = lookMemoryCorrect v st && validPC st (addPC 1 (lookMemory v st))
vmStepCorrect (ISet v) st
  = setMemoryCorrect v st && validPC st (addPC 1 (setMemory v st))
vmStepCorrect IAdd st
  = stackOpCorrect st && validPC st (addPC 1 (stackOp (+) st))
vmStepCorrect ISub st
  = stackOpCorrect st && validPC st (addPC 1 (stackOp (-) st))
vmStepCorrect (IJump n) st
  = addPCCorrect n st
vmStepCorrect (IJumpEq n) st
  = condJumpCorrect (==) n st
vmStepCorrect (IJumpNeq n) st
  = condJumpCorrect (/=) n st
vmStepCorrect IHalt _
  = True

-- property eight: instruction lookup

nextInstrCorrect :: [Instr] -> VMState -> Bool
nextInstrCorrect is st
  = nextInstr is st == atPos (pc st) is
    where
      atPos _ [] = Nothing
      atPos 0 (x : _) = if x == IHalt then Nothing
                         else Just x
      atPos n (_ : xs) = atPos n xs


nextInstrProp :: Property
nextInstrProp
  = forAll (vectorOf 20 (arbitrary :: Gen Instr))
           (forAll (arbitrary :: Gen VMState) . nextInstrCorrect)


-- tests
 
tests :: TestTree
tests = testGroup "Properties"
                  [ QC.testProperty "push correct" pushCorrect
                  , QC.testProperty "lookMemory correct" lookMemoryCorrect
                  , QC.testProperty "setMemory correct" setMemoryCorrect
                  , QC.testProperty "stackOp correct" stackOpCorrect
                  , QC.testProperty "addPC correct" addPCCorrect
                  , QC.testProperty "vmStep correct" vmStepCorrect
                  , QC.testProperty "nextInstrCorrect" nextInstrProp
                  ]

main :: IO ()
main = defaultMain tests
