
#define NO_OF_PIECES 2

#if DEBUG
#define debug(x) Serial.print(x)
#define debugln(x) Serial.println(x)
#define debugf(x, y) Serial.printf(x, y)

#else 

#define debug(x) 
#define debugln(x)
#define debugf(x, y)

#endif
