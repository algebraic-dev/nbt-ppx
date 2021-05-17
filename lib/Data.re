type i8;
type i16;
type i32;
type i64;
type double;

type tag('a) = (string, 'a);

type ext =
  | T(nbt('a)): ext

and nbt('a) =
  | TByte(int): nbt(i8)
  | TShort(int): nbt(i16)
  | TInt(int): nbt(i32)
  | TLong(int): nbt(i64)
  | TFloat(float): nbt(float)
  | TDouble(float): nbt(double)
  | TByteArray(Bytes.t): nbt(list(i8))
  | TString(string): nbt(string)
  | TList(list(nbt('a))): nbt(list(nbt('a)))
  | TCompound(list(tag(ext))): nbt(list(tag(ext)))
  | TIntArray(list(int)): nbt(list(i32))
  | TLongArray(list(int)): nbt(list(i64));
