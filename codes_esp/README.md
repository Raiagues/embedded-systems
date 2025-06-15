https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/index.html

### Set up the Environment Variables

`esp`

### Configure the Project

`idf.py set-target esp32`

### Combine bulding, flashing and monitoring 

`idf.py -p /dev/ttyUSB0 flash monitor`

### Exit IDF monitor

`Ctrl+]`

### Clean a build 

`idf.py fullclean`

## Create a project

`idf.py create-project -p . project_name`

## Open menuconfig

`idf.py menuconfig`
