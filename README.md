# JSParser
这是一个简易的JavaScript解释器，用于学习交流。仅支持部分常用语法,能够生成语法树，且支持算术、逻辑表达式的解释执行。

## 用法
使用Visual Studio 2017编译，编译后使用命令行进入Debug目录

1. 进入交互模式

```
>JSParser
```

2. 进入交互模式并显示语法树
```
>JSParser tree
```

3. 从外部文件读入代码并显示语法树
```
>JSParser file filepath
```

4. 仅进行词法分析
```
>JSParser token
```

5. 打开帮助
```
>JSParser help
```

## 支持语法

### 表达式

1. 数组
```
>>>[1,a,function(){}];
Array Expression
```

2. 赋值表达式
```
>>>a=30;
30
```

3. 算术表达式
```
>>>1+2*3/4*(5+6);
17.5
```

4. 布尔表达式
```
>>>!(true||false);
false
```

5. 函数表达式

```
>>>var func = function(a,b){};
Variable Declaration
```

6. 函数调用表达式
```
>>>func(a,b);
Call Expression
```

7. new表达式
```
>>>new Array();
New Expression
```

8. 更新表达式（自增自减）
```
>>>var a=10;
Variable Declaration
>>>++a;
11
```

9. 顺序表达式
```
>>>a=12,b=10;
Sequence Expression
```

### 语句

1. 声明语句（变量声明、函数声明）
```
>>>var a;
Variable Declaration
>>>var b=10;
Variable Declaration
>>>var c=b;
Variable Declaration
>>>function func(a,b){}
Function Declaration
```

2. If-Else语句
```
>>>if(a<5){
}else{
}
If Statement
>>>if(a>0){
};
If Statement
```

3. Do-While语句
```
>>>do{
a++;
}while(a<10);
Do While Statement
```

4. For语句
```
>>>for(var i=0;i<10;i++){
}
For Statement
```

5. Return语句
```
>>>function func(){
return;
}
Function Declaration
```

6. While语句
```
>>>while(a>0){
}
While Statement
```

7. Block语句
```
>>>{
var a=12;
}
Block Statement
```


