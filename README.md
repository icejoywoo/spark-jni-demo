# Spark jni demo

文章：http://icejoywoo.github.io/2018/07/25/spark-jni.html
使用的 base64 库：https://github.com/tkislan/base64

## 编译方法

```bash
javac Base64.java
jar cf base64.jar Base64.class
```

本地测试方法

```bash
java Base64
```

## Spark 测试

启动 spark-shell

```bash
$ spark-shell --files libbase64.so --jars base64.jar \
    --conf spark.executor.extraJavaOptions='-Djava.library.path=./' \
    --conf spark.driver.extraJavaOptions='-Djava.library.path=./' \
    --master yarn \
    --queue <queue_name> \
    --num-executors 10 \
    --executor-cores 4 \
    --executor-memory 5G \
    --driver-memory 5G
```

参数注意事项：--files 传入 so 动态库，--jars 传入 jar 包，需要额外配置 java.library.path。

当然配置环境变量 LD\_LIBRARY\_PATH 也是可以的。

测试代码

```scala
val rows = spark.read.format("text").load("/path/to/base64_encoded_string_files")

import org.apache.spark.sql.types._

val schema = StructType(
  StructField("value",StringType,true) ::
  Nil
)

val encoder = org.apache.spark.sql.catalyst.encoders.RowEncoder(schema)

val df = rows.map(row => {
  // implements java.io.Serializable 就不会报序列化错误
  val base64 = new Base64()
  val buffer = row.toSeq.toBuffer
  val line = buffer(0).asInstanceOf[String]
  org.apache.spark.sql.Row.fromSeq(Array(Base64.decode(line.stripLineEnd)))
})(encoder)

df.show()
```
