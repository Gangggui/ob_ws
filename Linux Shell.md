#### 判断cpu架构
```shell
#!/bin/bash

get_arch=`arch`
if [[ $get_arch =~ "x86_64" ]];then
    echo "this is x86_64"
elif [[ $get_arch =~ "aarch64" ]];then
    echo "this is arm64"
elif [[ $get_arch =~ "mips64" ]];then
    echo "this is mips64"
else
    echo "unknown!!"
fi

```

