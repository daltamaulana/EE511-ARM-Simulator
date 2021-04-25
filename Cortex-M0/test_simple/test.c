/*********************************************************
 *                                                       *
 *  EE511 Project 1                                      *
 *                                                       *
 *  C test code                                          *
 *                                                       *
 *********************************************************/

/*your test code here*/
int main(void)
{
  // Declare variable
  int i;
  int a = 1000;
  int result = 0;
  int x = 1;
  int y = 2;

  // Loop
  for (i=0; i<a; i++) {
    result += x + y + 1;
    x = x * 2;
    y = y * 2;
  }
  
  return 0;
}

