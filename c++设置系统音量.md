```c++
char command[50];  
int volum = 75;
sprintf(command, "pactl set-sink-volume @DEFAULT_SINK@ %d%%", volum;  
system(command);
```
