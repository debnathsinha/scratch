#include <stdio.h>
#include <stdlib.h>
#include "control.h"
#include "queue.h"
#include "dbug.h"

struct work_q {
  data_control control;
  queue work;
} wq;
