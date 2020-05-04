bool function(int x, int y, int z, int w) = 
if let z = x+y in w then
   x = z + w
else
   x = z + y
   
int func(int a, bool b) = 
if b then
   a = a+x
else
   a = a+y
   
int sum(int n, int m) = 
   sum = n + m