
### how to include xjson?
download xjson.hpp and put: 
> ```c++
> #include "xjson.hpp"
> ``` 

## how to write to file?

### single data
to write single key n value (s) put:
```c++
xjson().write(tmap<std::string>{"key", "value"}, "basic.txt");
  ```

### grouped data
to write a group put:
```c++
 xjson::group().write(groups<std::string>{ 
   { /* a group element goes here */ }
 }, "group.txt");
``` 
to put an key n value inside this group put (INSIDE GROUP):
```c++

			"group_name",
			{
				{ "key", "value" },
				{ "another_key", "another_value" }
			}
```
should look something like this:
```c++
xjson::group().write(groups<std::string>{ {
			"group_name",
			{
				{ "key", "value" },
				{ "another_key", "another_value" }
			}},
			{ "group_name2",
			{
				{ "key", "value" }
			}
			}}, "group.txt");
```

## how to read a file? 

### single data

```c++
for (auto& it : xjson().string("key", "basic.txt")) it.first; // -> key
for (auto& it : xjson().string("key", "basic.txt")) it.second; // -> value
```

### grouped data

```c++
for (auto& it : xjson::group().string("group_name", "group.txt")) 
		if (it.first == "key") it.second; // -> it.first = key; it.second = value
```
