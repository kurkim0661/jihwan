매크로를 이용한 static 멤버생성및 활용.

#define datalist \
X(name, type, len)\
X(name, type, len)\
X(name, type, len)\
X(name, type, len)

#ifdef X
#undef X
#define X(string, type, len) string,
enum ID
{
  datalist
};
#undef X



static inline a_namespace::struct (*get_list_info(void))[size + 1]
{
#ifdef X
#undef X
#endif 
#ifdef NAME_SPACE_CAST
#undef NAME_SPACE_CAST
#endif
#define NAME_SPACE_CAST(NameSpace, x) NameSpace::x
#define MAKE_STRING(arg) #arg
#define X(string, type, len) { #string, MAKE_STRING(pwd), NAME_SPACE_CAST(namespace, type), len},
static a_namespace::struct list[] =
{
  datalist
};
#undef X
#undef MAKE_STRING
#undef NAME_SPACE_CAST
  return &list;
}


#define datalist \
X(name, type, len)\
X(name, type, len)\
X(name, type, len)\
X(name, type, len)

