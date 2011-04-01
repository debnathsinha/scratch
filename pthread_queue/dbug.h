#define dabort() \
  { printf("Aborting @ line %d in src file %s\n", __LINE__, __FILE__ ); \
    abort(); }
