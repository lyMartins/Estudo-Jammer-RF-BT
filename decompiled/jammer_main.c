// === FUN_00006530 @ 0x6530 ===

/* WARNING: Control flow encountered bad instruction data */

void FUN_00006530(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// === FUN_00022a90 @ 0x22a90 ===

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00022a90(undefined4 param_1)

{
  int *piVar1;
  
  piVar1 = _DAT_fff60080;
  memw();
  memw();
  *_DAT_fff60080 = *_DAT_fff60080 + 1;
  memw();
  if (4 < *piVar1) {
    memw();
    *piVar1 = 1;
  }
  return param_1;
}



// === FUN_00022ab4 @ 0x22ab4 ===

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

byte * FUN_00022ab4(void)

{
  byte **ppbVar1;
  byte *pbVar2;
  byte *pbVar3;
  byte bVar4;
  uint uVar5;
  uint unaff_a13;
  undefined4 unaff_a14;
  int iVar6;
  
  iVar6 = FUN_000271b0();
  pbVar2 = _DAT_fff600fc;
  if (*_DAT_fff600fc == 0) {
    uVar5 = 0x95;
    if ((uint)(iVar6 - *_DAT_fff60100) < 0x96) {
      return _DAT_fff600fc;
    }
  }
  else {
    unaff_a14 = 1000;
    unaff_a13 = 0x96;
    uVar5 = iVar6 - *_DAT_fff60100;
    if (*_DAT_fff60104 == *_DAT_fff60108) {
      unaff_a13 = 1000;
    }
    if (uVar5 < unaff_a13) {
      return _DAT_fff600fc;
    }
  }
  bVar4 = *_DAT_fff600fc ^ 1;
  *_DAT_fff60100 = iVar6;
  *pbVar2 = bVar4;
  FUN_00026cb8(0x1b,bVar4,uVar5,unaff_a13,unaff_a14);
  ppbVar1 = _DAT_fff60104;
  pbVar2 = (byte *)(uint)*pbVar2;
  if (pbVar2 != (byte *)0x0) {
    pbVar3 = *_DAT_fff60104;
    pbVar2 = *_DAT_fff60108;
    *_DAT_fff60104 = pbVar3 + 1;
    if ((int)pbVar2 < (int)(pbVar3 + 1)) {
      pbVar2 = (byte *)0x1;
      *ppbVar1 = (byte *)0x1;
    }
  }
  return pbVar2;
}



// === FUN_00022b24 @ 0x22b24 ===

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_00022b24(void)

{
  int *piVar1;
  int iVar2;
  undefined4 unaff_a10;
  undefined4 unaff_a11;
  undefined4 uVar3;
  
  piVar1 = _DAT_fff6010c;
  iVar2 = *_DAT_fff6010c;
  if (iVar2 != 1) {
    iVar2 = 1;
    FUN_00026694(_DAT_fff60028,_DAT_fff60110);
    uVar3 = _DAT_fff60114;
    *piVar1 = 1;
    uVar3 = FUN_00023674(uVar3,0);
    uVar3 = FUN_000271b0(uVar3,0);
    unaff_a11 = 0;
    *_DAT_fff60100 = uVar3;
    *_DAT_fff60104 = 0;
    *_DAT_fff600fc = 0;
    unaff_a10 = FUN_00026cb8(0x1b,0);
    *_DAT_fff60108 = 1;
  }
  FUN_00022ab4(unaff_a10,unaff_a11);
  return iVar2;
}



// === FUN_00022b6c @ 0x22b6c ===

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_00022b6c(void)

{
  int *piVar1;
  int iVar2;
  undefined4 unaff_a10;
  undefined4 unaff_a11;
  undefined4 uVar3;
  
  piVar1 = _DAT_fff6010c;
  iVar2 = *_DAT_fff6010c;
  if (iVar2 != 2) {
    iVar2 = 2;
    FUN_00026694(_DAT_fff60028,_DAT_fff60118);
    uVar3 = _DAT_fff6011c;
    *piVar1 = 2;
    uVar3 = FUN_00023674(uVar3,0);
    uVar3 = FUN_000271b0(uVar3,0);
    unaff_a11 = 0;
    *_DAT_fff60100 = uVar3;
    *_DAT_fff60104 = 0;
    *_DAT_fff600fc = 0;
    unaff_a10 = FUN_00026cb8(0x1b,0);
    *_DAT_fff60108 = 2;
  }
  FUN_00022ab4(unaff_a10,unaff_a11);
  return iVar2;
}



// === FUN_00022bb4 @ 0x22bb4 ===

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_00022bb4(void)

{
  int *piVar1;
  int iVar2;
  undefined4 unaff_a10;
  undefined4 unaff_a11;
  undefined4 uVar3;
  
  piVar1 = _DAT_fff6010c;
  iVar2 = *_DAT_fff6010c;
  if (iVar2 != 3) {
    iVar2 = 3;
    FUN_00026694(_DAT_fff60028,_DAT_fff60120);
    uVar3 = _DAT_fff60124;
    *piVar1 = 3;
    uVar3 = FUN_00023674(uVar3,0);
    uVar3 = FUN_000271b0(uVar3,0);
    unaff_a11 = 0;
    *_DAT_fff60100 = uVar3;
    *_DAT_fff60104 = 0;
    *_DAT_fff600fc = 0;
    unaff_a10 = FUN_00026cb8(0x1b,0);
    *_DAT_fff60108 = 3;
  }
  FUN_00022ab4(unaff_a10,unaff_a11);
  return iVar2;
}



// === FUN_00022bfc @ 0x22bfc ===

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_00022bfc(void)

{
  int *piVar1;
  int iVar2;
  undefined4 unaff_a10;
  undefined4 unaff_a11;
  undefined4 uVar3;
  
  piVar1 = _DAT_fff6010c;
  iVar2 = *_DAT_fff6010c;
  if (iVar2 != 4) {
    iVar2 = 4;
    FUN_00026694(_DAT_fff60028,_DAT_fff60128);
    uVar3 = _DAT_fff6012c;
    *piVar1 = 4;
    uVar3 = FUN_00023674(uVar3,0);
    uVar3 = FUN_000271b0(uVar3,0);
    unaff_a11 = 0;
    *_DAT_fff60100 = uVar3;
    *_DAT_fff60104 = 0;
    *_DAT_fff600fc = 0;
    unaff_a10 = FUN_00026cb8(0x1b,0);
    *_DAT_fff60108 = 4;
  }
  FUN_00022ab4(unaff_a10,unaff_a11);
  return iVar2;
}



// === FUN_00022c44 @ 0x22c44 ===

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00022c44(void)

{
  undefined4 uVar1;
  
  uVar1 = _DAT_fff60130;
  FUN_00023970(_DAT_fff60024,0x10,0xf,_DAT_fff60130);
  FUN_00023970(_DAT_fff60054,0x16,0x15,uVar1);
  FUN_000240a0(_DAT_fff6009c,0,0x15,uVar1);
  return uVar1;
}



// === FUN_00022c70 @ 0x22c70 ===

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_00022c70(void)

{
  longlong lVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  undefined4 unaff_a10;
  undefined *puVar6;
  undefined4 unaff_a11;
  undefined *puVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  undefined4 uVar15;
  undefined auStack_64 [16];
  undefined auStack_54 [16];
  undefined auStack_44 [16];
  undefined auStack_34 [16];
  int iStack_24;
  
  uVar8 = _DAT_fff60140;
  piVar3 = _DAT_fff60134;
  piVar2 = _DAT_fff6010c;
  memw();
  iStack_24 = *_DAT_fff60134;
  memw();
  if (*_DAT_fff6010c != 0) {
    unaff_a10 = FUN_00026694(_DAT_fff60028,_DAT_fff60140);
    *piVar2 = 0;
    unaff_a11 = uVar8;
  }
  uVar11 = FUN_000233ac(unaff_a10,unaff_a11);
  iVar12 = FUN_000233bc(uVar11,unaff_a11);
  iVar13 = FUN_00023620(iVar12,unaff_a11);
  piVar2 = _DAT_fff60144;
  *_DAT_fff60144 = *_DAT_fff60144 + 1;
  iVar4 = _DAT_fff60148;
  FUN_00025ac4(_DAT_fff60148,unaff_a11);
  FUN_000258a0(iVar4,1);
  uVar8 = _DAT_fff6014c;
  *(undefined4 *)(iVar4 + 0x10) = 0;
  FUN_0002666c(iVar4,uVar8);
  iVar14 = FUN_000239e8(_DAT_fff60024,uVar8);
  uVar8 = _DAT_fff60138;
  if (iVar14 == 0) {
    uVar8 = _DAT_fff6013c;
  }
  FUN_0002666c(iVar4,uVar8);
  uVar8 = _DAT_fff60154;
  *(undefined4 *)(iVar4 + 0x10) = _DAT_fff60150;
  FUN_0002666c(iVar4,uVar8);
  iVar14 = FUN_000239e8(_DAT_fff60054,uVar8);
  uVar8 = _DAT_fff60138;
  if (iVar14 == 0) {
    uVar8 = _DAT_fff6013c;
  }
  FUN_0002666c(iVar4,uVar8);
  if (iVar13 == 1) {
    (*_DAT_fff60198)(iVar4,0x3c,10,8,0xc,1);
    (*_DAT_fff6019c)(iVar4,0x3d,0xb,6,3,1);
    (*_DAT_fff6019c)(iVar4,0x38,0x10,0x10,2,1);
    (*_DAT_fff6019c)(iVar4,0x36,0x14,4,2,1);
    (*_DAT_fff6019c)(iVar4,0x3e,0x14,4,2,1);
    uVar10 = 2;
    uVar9 = 4;
    uVar8 = 0x14;
    (*_DAT_fff6019c)(iVar4,0x46,0x14,4,2,1);
    FUN_000258a0(iVar4,1,0x14,4,2,1);
    uVar15 = _DAT_fff6015c;
    *(undefined4 *)(iVar4 + 0x10) = _DAT_fff60158;
    FUN_0002666c(iVar4,uVar15,0x14,4,2,1);
    iVar13 = _DAT_fff60168;
    iVar12 = *piVar2;
    uVar5 = (int)((longlong)iVar12 * (longlong)_DAT_fff60160 >> 0x22) - (iVar12 >> 0x1f) &
            _DAT_fff60164;
    if ((int)uVar5 < 0) {
      uVar5 = (uVar5 - 1 | 0xfffffffc) + 1;
    }
    FUN_000269e8(auStack_34,_DAT_fff60168,0x14,4,2,1);
    iVar12 = _DAT_fff6016c;
    for (iVar14 = 0; iVar14 < (int)uVar5; iVar14 = iVar14 + 1) {
      FUN_00026b50(auStack_34,iVar12,0x14,4,2,1);
      iVar13 = iVar12;
    }
    iVar13 = (*_DAT_fff601a0)(auStack_34,iVar13,0x14,4,2,1);
    *(short *)(iVar4 + 0x10) = (short)(iVar13 * -6 + 0x80U >> 1);
    *(undefined2 *)(iVar4 + 0x12) = 0x26;
    puVar7 = auStack_34;
    (*_DAT_fff601a4)(iVar4,puVar7,0x14,4,2,1);
    puVar6 = auStack_34;
    while( true ) {
      FUN_00026850(puVar6,puVar7,uVar8,uVar9,uVar10,1);
LAB_00022ed9:
      uVar15 = FUN_00025f7c(iVar4,puVar7,uVar8,uVar9,uVar10,1);
      memw();
      memw();
      iVar4 = *piVar3;
      if (iStack_24 == iVar4) break;
      iVar14 = func_0xfffd2e5c(uVar15,puVar7,uVar8,uVar9,uVar10,1);
LAB_00022ef8:
      (*_DAT_fff60198)(iVar14,puVar7,uVar8,uVar9,uVar10,1);
      uVar10 = 8;
      uVar9 = 3;
      uVar8 = 0xf;
      (*_DAT_fff6019c)(iVar4,0x54,0xf,3,8,1);
      lVar1 = (longlong)_DAT_fff60188;
      for (iVar13 = 0; iVar13 < (int)((iVar12 + 0x18) * lVar1 >> 0x23) - (iVar12 + 0x18 >> 0x1f);
          iVar13 = iVar13 + 1) {
        uVar10 = 0xe;
        uVar9 = 8;
        uVar8 = 0xc;
        (*_DAT_fff6019c)(iVar4,(iVar13 * 9 + 0x2e) * 0x10000 >> 0x10,0xc,8,0xe,1);
      }
      FUN_000258a0(iVar4,1,uVar8,uVar9,uVar10,1);
      FUN_00026a6c(auStack_44,iVar12,10,uVar9,uVar10,1);
      FUN_00026a38(auStack_34,auStack_44,10,uVar9,uVar10,1);
      uVar8 = FUN_00026bb4(auStack_34,_DAT_fff6018c,10,uVar9,uVar10,1);
      FUN_00026a38(auStack_64,uVar8,10,uVar9,uVar10,1);
      FUN_00026850(auStack_34,uVar8,10,uVar9,uVar10,1);
      FUN_00026850(auStack_44,uVar8,10,uVar9,uVar10,1);
      iVar13 = (*_DAT_fff601a0)(auStack_64,uVar8,10,uVar9,uVar10,1);
      *(short *)(iVar4 + 0x10) = (short)(iVar13 * -6 + 0x80U >> 1);
      *(undefined2 *)(iVar4 + 0x12) = 0x23;
      (*_DAT_fff601a4)(iVar4,auStack_64,10,uVar9,uVar10,1);
      FUN_000269e8(auStack_34,_DAT_fff60190,10,uVar9,uVar10,1);
      uVar8 = 2;
      FUN_00026aa8(auStack_44,uVar11,2,uVar9,uVar10,1);
      uVar15 = FUN_00026b84(auStack_34,auStack_44,2,uVar9,uVar10,1);
      uVar15 = FUN_00026bb4(uVar15,_DAT_fff60194,2,uVar9,uVar10,1);
      FUN_00026a38(auStack_54,uVar15,2,uVar9,uVar10,1);
      FUN_00026850(auStack_44,uVar15,2,uVar9,uVar10,1);
      FUN_00026850(auStack_34,uVar15,2,uVar9,uVar10,1);
      iVar13 = (*_DAT_fff601a0)(auStack_54,uVar15,2,uVar9,uVar10,1);
      *(short *)(iVar4 + 0x10) = (short)(iVar13 * -6 + 0x80U >> 1);
      *(undefined2 *)(iVar4 + 0x12) = 0x30;
      puVar7 = auStack_54;
      (*_DAT_fff601a4)(iVar4,puVar7,2,uVar9,uVar10,1);
      FUN_00026850(auStack_54,puVar7,2,uVar9,uVar10,1);
      puVar6 = auStack_64;
    }
    return iVar4;
  }
  uVar10 = 0x12;
  uVar9 = 0x28;
  uVar8 = 10;
  puVar7 = (undefined *)0x2c;
  iVar14 = iVar4;
  if (iVar13 != 2) goto LAB_00022ef8;
  (*_DAT_fff60198)(iVar4,0x2c,10,0x28,0x12,1);
  uVar10 = 8;
  uVar9 = 3;
  uVar8 = 0xf;
  (*_DAT_fff6019c)(iVar4,0x54,0xf,3,8,1);
  iVar12 = *piVar2;
  if (iVar12 < 0) {
    iVar12 = iVar12 + 7;
  }
  uVar5 = iVar12 >> 3 & _DAT_fff60164;
  if ((int)uVar5 < 0) {
    uVar5 = (uVar5 - 1 | 0xfffffffc) + 1;
  }
  iVar12 = 1;
  for (iVar13 = 0; iVar13 <= (int)uVar5; iVar13 = iVar13 + 1) {
    uVar10 = 0xe;
    uVar9 = 8;
    uVar8 = 0xc;
    (*_DAT_fff6019c)(iVar4,iVar13 * 9 + 0x2e,0xc,8,0xe,1);
  }
  FUN_000258a0(iVar4,1,uVar8,uVar9,uVar10,1);
  uVar15 = _DAT_fff60174;
  *(undefined4 *)(iVar4 + 0x10) = _DAT_fff60170;
  FUN_0002666c(iVar4,uVar15,uVar8,uVar9,uVar10,1);
  uVar15 = _DAT_fff6017c;
  *(undefined4 *)(iVar4 + 0x10) = _DAT_fff60178;
  FUN_0002666c(iVar4,uVar15,uVar8,uVar9,uVar10,1);
  puVar7 = _DAT_fff60184;
  *(undefined4 *)(iVar4 + 0x10) = _DAT_fff60180;
  FUN_0002666c(iVar4,puVar7,uVar8,uVar9,uVar10,1);
  goto LAB_00022ed9;
}



// === FUN_0002309c @ 0x2309c ===

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

char FUN_0002309c(void)

{
  char cVar1;
  char *pcVar2;
  int *piVar3;
  undefined4 uVar4;
  uint *puVar5;
  char *pcVar6;
  char *pcVar7;
  int iVar8;
  uint uVar9;
  
  uVar4 = _DAT_fff6009c;
  FUN_000240d4(_DAT_fff6009c);
  uVar9 = FUN_00026cc8(0);
  pcVar6 = _DAT_fff601ac;
  puVar5 = _DAT_fff601a8;
  piVar3 = _DAT_fff60080;
  pcVar2 = _DAT_fff6007c;
  if (uVar9 == 0) {
    if (*_DAT_fff601a8 == 0) {
      uVar9 = FUN_000271b0(0);
      *puVar5 = uVar9;
    }
    else {
      memw();
      if ((*_DAT_fff6007c == '\0') && (*_DAT_fff601ac == '\0')) {
        iVar8 = FUN_000271b0(0);
        uVar9 = iVar8 - *puVar5;
        if (499 < uVar9) {
          memw();
          memw();
          *_DAT_fff601b0 = *piVar3;
          memw();
          *piVar3 = 0;
          memw();
          *pcVar2 = '\x01';
          *pcVar6 = '\x01';
        }
      }
    }
  }
  else if (*_DAT_fff601a8 != 0) {
    iVar8 = FUN_000271b0(uVar9);
    pcVar6 = _DAT_fff601ac;
    memw();
    uVar9 = iVar8 - *puVar5;
    if ((uVar9 < 500) && (*pcVar2 != '\0')) {
      memw();
      iVar8 = *_DAT_fff601b0;
      *_DAT_fff601ac = '\0';
      memw();
      *piVar3 = iVar8;
      pcVar7 = _DAT_fff601b4;
      memw();
      *pcVar2 = '\0';
      *pcVar7 = '\x01';
      *_DAT_fff6010c = 0;
      memw();
      iVar8 = *piVar3;
      if (iVar8 == 2) {
        uVar9 = FUN_00022b6c(uVar9);
      }
      else if (iVar8 < 3) {
        if (iVar8 == 1) {
          uVar9 = FUN_00022b24(uVar9);
        }
      }
      else if (iVar8 == 3) {
        uVar9 = FUN_00022bb4(uVar9);
      }
      else if (iVar8 == 4) {
        uVar9 = FUN_00022bfc(uVar9);
      }
    }
    *puVar5 = 0;
    *pcVar6 = '\0';
  }
  memw();
  cVar1 = *pcVar2;
  if ((cVar1 == '\0') && (uVar9 = (*_DAT_fff601b8)(uVar4), uVar9 != 0)) {
    if (*_DAT_fff601b4 == '\0') {
      uVar9 = FUN_00022a90(uVar9);
    }
    else {
      *_DAT_fff601b4 = '\0';
    }
  }
  memw();
  iVar8 = *piVar3;
  if (iVar8 == 2) {
    FUN_00022b6c(uVar9);
  }
  else if (iVar8 < 3) {
    if (iVar8 == 0) {
      FUN_00022c70(uVar9);
    }
    else if (iVar8 == 1) {
      FUN_00022b24(uVar9);
    }
  }
  else if (iVar8 == 3) {
    FUN_00022bb4(uVar9);
  }
  else if (iVar8 == 4) {
    FUN_00022bfc(uVar9);
  }
  return cVar1;
}



// === FUN_00023208 @ 0x23208 ===

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00023208(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  
  iVar2 = 0x10;
  iVar1 = 0;
  uVar5 = 0;
  do {
    iVar4 = FUN_0002d468(param_1);
    uVar3 = uVar5 + iVar4;
    iVar2 = iVar2 + -1;
    iVar1 = (uint)(uVar3 < uVar5) + iVar1 + (iVar4 >> 0x1f);
    uVar5 = uVar3;
  } while (iVar2 != 0);
  uVar5 = FUN_00050970(iVar1 * 0x10000000 | uVar3 >> 4,*_DAT_fff601bc);
  uVar6 = (*_DAT_fff601c4)(1.0 / (float)(ulonglong)uVar5,_DAT_fff601c0);
  return uVar6;
}



// === FUN_00023254 @ 0x23254 ===

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float FUN_00023254(void)

{
  int *piVar1;
  float *pfVar2;
  int *piVar3;
  float *pfVar4;
  byte *pbVar5;
  byte bVar6;
  float fVar7;
  int iVar8;
  int iVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  
  fVar10 = (float)FUN_00023208(6);
  fVar11 = (float)FUN_00023208(5);
  fVar13 = _DAT_fff6020c;
  pbVar5 = _DAT_fff60204;
  pfVar4 = _DAT_fff60200;
  fVar14 = _DAT_fff601fc;
  piVar3 = _DAT_fff601f8;
  pfVar2 = _DAT_fff601f4;
  piVar1 = _DAT_fff601f0;
  iVar9 = *_DAT_fff601f0;
  fVar12 = *_DAT_fff601e8 + fVar10 * _DAT_fff601ec;
  fVar10 = _DAT_fff601ec;
  fVar7 = _DAT_fff601c8;
  if ((iVar9 == 1) &&
     (fVar10 = _DAT_fff601d4, fVar7 = _DAT_fff601cc, _DAT_fff601d4 <= *_DAT_fff601f4)) {
    fVar7 = _DAT_fff601c8;
  }
  iVar8 = *_DAT_fff601f8;
  if (fVar7 <= fVar12) {
    fVar10 = _DAT_fff601d4;
    if ((_DAT_fff601d4 <= fVar12) && (fVar10 = fVar12, _DAT_fff601d0 < fVar12)) {
      fVar10 = _DAT_fff601d0;
    }
    if (_DAT_fff601d4 <= *_DAT_fff601f4) {
      fVar14 = *_DAT_fff60200 * _DAT_fff60208;
      *_DAT_fff601f4 = *_DAT_fff601f4 * _DAT_fff60208 + fVar10 * _DAT_fff6020c;
      *pfVar4 = fVar14 + fVar11 * fVar13;
    }
    else {
      *_DAT_fff601f4 = fVar10;
      *pfVar4 = fVar11;
    }
    fVar10 = _DAT_fff601e0;
    fVar14 = _DAT_fff601e4;
    fVar13 = _DAT_fff601e0;
    if ((iVar9 != 2) && (fVar14 = _DAT_fff601dc, fVar13 = _DAT_fff601d8, iVar9 != 1)) {
      fVar14 = _DAT_fff601e4;
    }
    iVar9 = 2;
    if ((*pfVar4 < fVar13) && (iVar9 = 1, *pfVar4 < fVar14)) {
      iVar9 = 0;
    }
    if (iVar9 == iVar8) {
      if ((*pbVar5 < 6) && (bVar6 = *pbVar5 + 1, *pbVar5 = bVar6, bVar6 != 6)) {
        return fVar10;
      }
LAB_0002333e:
      *piVar1 = iVar8;
      return fVar10;
    }
    *piVar3 = iVar9;
    bVar6 = 1;
  }
  else {
    *_DAT_fff60200 = fVar11;
    *pfVar2 = fVar14;
    if (iVar8 == 1) {
      if (5 < *pbVar5) goto LAB_0002333e;
      bVar6 = *pbVar5 + 1;
    }
    else {
      bVar6 = 1;
      *piVar3 = 1;
    }
  }
  *pbVar5 = bVar6;
  return fVar10;
}



// === FUN_00023390 @ 0x23390 ===

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00023390(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_000271b0();
  if (0x13 < (uint)(iVar1 - *_DAT_fff60210)) {
    *_DAT_fff60210 = iVar1;
    FUN_00023254(iVar1,0x13);
  }
  return param_1;
}



// === FUN_000233ac @ 0x233ac ===

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_000233ac(void)

{
  FUN_00023390();
  return *_DAT_fff601f4;
}



// === FUN_000233bc @ 0x233bc ===

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_000233bc(void)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  FUN_00023390();
  fVar2 = *_DAT_fff601f4;
  if (_DAT_fff60214 <= fVar2) {
    return 100;
  }
  if (fVar2 < _DAT_fff60218) {
    if (_DAT_fff60228 <= fVar2) {
      fVar1 = (float)(*_DAT_fff601c4)(fVar2 - _DAT_fff60228,_DAT_fff6022c);
      fVar2 = _DAT_fff60220;
      fVar3 = _DAT_fff60230;
    }
    else if (_DAT_fff60234 <= fVar2) {
      fVar1 = (float)(*_DAT_fff601c4)(fVar2 - _DAT_fff60234,_DAT_fff6022c);
      fVar2 = _DAT_fff60238;
      fVar3 = _DAT_fff6023c;
    }
    else {
      if (fVar2 < _DAT_fff60240) {
        if (fVar2 < _DAT_fff60248) {
          if (_DAT_fff6024c <= fVar2) {
            fVar2 = (float)(*_DAT_fff601c4)(fVar2 - _DAT_fff6024c,_DAT_fff6022c);
            fVar3 = _DAT_fff60220;
          }
          else {
            if (fVar2 < _DAT_fff60250) {
              if (fVar2 < _DAT_fff60258) {
                if (fVar2 < _DAT_fff60260) {
                  return 0;
                }
                fVar3 = (float)(*_DAT_fff601c4)(fVar2 - _DAT_fff60260,_DAT_fff6022c);
                goto LAB_00023407;
              }
              fVar1 = (float)(*_DAT_fff601c4)(fVar2 - _DAT_fff60258,_DAT_fff6022c);
              fVar2 = _DAT_fff60228;
              fVar3 = _DAT_fff6025c;
              goto LAB_00023401;
            }
            fVar2 = (float)(*_DAT_fff601c4)(fVar2 - _DAT_fff60250,_DAT_fff6022c);
            fVar3 = _DAT_fff60254;
          }
        }
        else {
          fVar2 = (float)(*_DAT_fff601c4)(fVar2 - _DAT_fff60248,_DAT_fff6022c);
          fVar3 = _DAT_fff60238;
        }
        fVar3 = fVar3 + fVar2 * fVar3;
        goto LAB_00023407;
      }
      fVar1 = (float)(*_DAT_fff601c4)(fVar2 - _DAT_fff60240,_DAT_fff6022c);
      fVar2 = _DAT_fff60238;
      fVar3 = _DAT_fff60244;
    }
  }
  else {
    fVar1 = (float)(*_DAT_fff601c4)(fVar2 - _DAT_fff60218,_DAT_fff6021c);
    fVar2 = _DAT_fff60220;
    fVar3 = _DAT_fff60224;
  }
LAB_00023401:
  fVar3 = fVar3 + fVar1 * fVar2;
LAB_00023407:
  return (int)(fVar3 * 1.0);
}



// === FUN_00023620 @ 0x23620 ===

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00023620(void)

{
  FUN_00023390();
  return *_DAT_fff601f0;
}



// === FUN_00023630 @ 0x23630 ===

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_00023630(void)

{
  int iVar1;
  int iVar2;
  
  FUN_00025204(_DAT_fff602a0,4,5,0);
  iVar1 = _DAT_fff60148;
  iVar2 = FUN_00025ae8(_DAT_fff60148,2,0x3c,1,1);
  if (iVar2 == 0) {
    FUN_00026694(_DAT_fff60028,_DAT_fff602a4,0x3c,1,1);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  FUN_00025ac4(iVar1,2,0x3c,1,1);
  *(undefined4 *)(iVar1 + 0x14) = _DAT_fff602a8;
  FUN_00025f7c(iVar1,2,0x3c,1,1);
  return iVar1;
}



// === FUN_00023674 @ 0x23674 ===

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_00023674(uint param_1,uint param_2)

{
  uint *puVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 unaff_a12;
  undefined4 unaff_a13;
  undefined4 unaff_a14;
  undefined4 unaff_a15;
  int iVar4;
  undefined4 uVar5;
  int aiStack_34 [2];
  uint uStack_2c;
  uint uStack_28;
  uint uStack_24;
  
  iVar2 = _DAT_fff60148;
  puVar1 = _DAT_fff60134;
  param_2 = param_2 & 0xff;
  memw();
  uStack_24 = *_DAT_fff60134;
  memw();
  FUN_00025ac4(_DAT_fff60148);
  uVar3 = _DAT_fff602ac;
  if (param_2 == 0) goto LAB_000236da;
  iVar4 = func_0xfffe10b8(param_1,_DAT_fff602ac);
  uVar5 = _DAT_fff602b0;
  if (iVar4 == 0) {
    unaff_a15 = 0x40;
    unaff_a14 = 0x80;
    (*_DAT_fff602d8)(iVar2,0,0,_DAT_fff602b0,0x80,0x40,1);
    uVar3 = 0;
    unaff_a12 = 0;
    unaff_a13 = uVar5;
  }
  while( true ) {
    uVar5 = FUN_00025f7c(iVar2,uVar3,unaff_a12,unaff_a13,unaff_a14,unaff_a15);
    param_2 = uStack_24;
    memw();
    memw();
    param_1 = *puVar1;
    if (uStack_24 == param_1) break;
    func_0xfffd2e5c(uVar5,uVar3,unaff_a12,unaff_a13,unaff_a14,unaff_a15);
LAB_000236da:
    FUN_000258a0(iVar2,1,unaff_a12,unaff_a13,unaff_a14,unaff_a15);
    uVar3 = _DAT_fff602b4;
    *(undefined4 *)(iVar2 + 0x14) = _DAT_fff602a8;
    FUN_000269e8(aiStack_34,uVar3,unaff_a12,unaff_a13,unaff_a14,unaff_a15);
    if ((int)uStack_28 < 0) {
      param_2 = uStack_28 >> 0x18 & 0x7f;
    }
    else if (aiStack_34[0] != 0) {
      param_2 = uStack_2c;
    }
    *(short *)(iVar2 + 0x10) = (short)(0x80 - ((int)(param_2 * 0x60000) >> 0x10) >> 1);
    *(undefined2 *)(iVar2 + 0x12) = 2;
    (*_DAT_fff601a4)(iVar2,aiStack_34,unaff_a12,unaff_a13,unaff_a14,unaff_a15);
    iVar4 = func_0xfffe10b8(param_1,_DAT_fff602b8,unaff_a12,unaff_a13,unaff_a14,unaff_a15);
    uVar5 = _DAT_fff602bc;
    if ((((iVar4 == 0) ||
         (iVar4 = func_0xfffe10b8(param_1,_DAT_fff602c0,unaff_a12,unaff_a13,unaff_a14,unaff_a15),
         uVar5 = _DAT_fff602c4, iVar4 == 0)) ||
        (iVar4 = func_0xfffe10b8(param_1,_DAT_fff602c8,unaff_a12,unaff_a13,unaff_a14,unaff_a15),
        uVar3 = _DAT_fff602d0, uVar5 = _DAT_fff602cc, iVar4 == 0)) ||
       (iVar4 = func_0xfffe10b8(param_1,_DAT_fff602d0,unaff_a12,unaff_a13,unaff_a14,unaff_a15),
       uVar5 = _DAT_fff602d4, iVar4 == 0)) {
      uVar3 = 0;
      unaff_a15 = 0x32;
      unaff_a14 = 0x80;
      unaff_a12 = 0xc;
      (*_DAT_fff602d8)(iVar2,0,0xc,uVar5,0x80,0x32,1);
      unaff_a13 = uVar5;
    }
    FUN_00026850(aiStack_34,uVar3,unaff_a12,unaff_a13,unaff_a14,unaff_a15);
  }
  return param_1;
}



// === FUN_000237d4 @ 0x237d4 ===

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_000237d4(undefined4 param_1)

{
  FUN_000258dc(_DAT_fff60148,0x80,0x40,_DAT_fff602a0,0xffffffff,_DAT_fff602dc,_DAT_fff602e0);
  return param_1;
}



// === FUN_000237f4 @ 0x237f4 ===

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_000237f4(undefined4 param_1)

{
  FUN_000258b4(_DAT_fff60148);
  return param_1;
}



// === FUN_00023800 @ 0x23800 ===

int FUN_00023800(int param_1,undefined param_2)

{
  FUN_00026cb8(*(undefined *)(param_1 + 5),param_2);
  FUN_000271d4(*(undefined4 *)(param_1 + 0x24),param_2);
  return param_1;
}



// === FUN_00023814 @ 0x23814 ===

char FUN_00023814(int param_1,undefined param_2)

{
  char cVar1;
  
  cVar1 = *(char *)(param_1 + 5);
  if (cVar1 != *(char *)(param_1 + 4)) {
    FUN_00026cb8(*(char *)(param_1 + 4),param_2);
  }
  return cVar1;
}



// === FUN_00023828 @ 0x23828 ===

undefined4 * FUN_00023828(undefined4 *param_1)

{
  FUN_00023ff8(*param_1,param_1[2],1);
  FUN_00023800(param_1,0,1);
  return param_1;
}



// === FUN_00023844 @ 0x23844 ===

undefined4 * FUN_00023844(undefined4 *param_1)

{
  FUN_00023800(param_1,1);
  FUN_00024040(*param_1,1);
  return param_1;
}



// === FUN_00023858 @ 0x23858 ===

undefined4 * FUN_00023858(undefined4 *param_1,undefined param_2,undefined *param_3,char param_4)

{
  undefined uVar1;
  
  FUN_00023828(param_1);
  uVar1 = FUN_00024064(*param_1,param_2);
  *(undefined *)(param_1 + 3) = uVar1;
  while (param_4 = param_4 + -1, param_4 != -1) {
    param_2 = 0xff;
    uVar1 = FUN_00024064(*param_1,0xff);
    *param_3 = uVar1;
    param_3 = param_3 + 1;
  }
  FUN_00023844(param_1,param_2);
  return param_1;
}



// === FUN_00023894 @ 0x23894 ===

undefined4 FUN_00023894(undefined4 *param_1,undefined param_2)

{
  undefined uVar1;
  undefined4 uVar2;
  
  FUN_00023828(param_1);
  uVar1 = FUN_00024064(*param_1,param_2);
  *(undefined *)(param_1 + 3) = uVar1;
  uVar2 = FUN_00024064(*param_1,0xff);
  FUN_00023844(param_1,0xff);
  return uVar2;
}



// === FUN_000238c0 @ 0x238c0 ===

undefined4 * FUN_000238c0(undefined4 *param_1,byte param_2,byte *param_3,char param_4)

{
  undefined uVar1;
  
  FUN_00023828(param_1);
  param_2 = param_2 | 0x20;
  uVar1 = FUN_00024064(*param_1,param_2);
  *(undefined *)(param_1 + 3) = uVar1;
  while (param_4 = param_4 + -1, param_4 != -1) {
    param_2 = *param_3;
    param_3 = param_3 + 1;
    FUN_00024064(*param_1,param_2);
  }
  FUN_00023844(param_1,param_2);
  return param_1;
}



// === FUN_000238fc @ 0x238fc ===

undefined4 * FUN_000238fc(undefined4 *param_1,byte param_2,undefined param_3)

{
  undefined uVar1;
  
  FUN_00023828(param_1);
  uVar1 = FUN_00024064(*param_1,param_2 | 0x20);
  *(undefined *)(param_1 + 3) = uVar1;
  FUN_00024064(*param_1,param_3);
  FUN_00023844(param_1,param_3);
  return param_1;
}



// === FUN_00023928 @ 0x23928 ===

undefined FUN_00023928(int param_1)

{
  FUN_00023858(param_1,0xe2,0,0);
  return *(undefined *)(param_1 + 0xc);
}



// === FUN_00023940 @ 0x23940 ===

undefined FUN_00023940(int param_1)

{
  FUN_00023858(param_1,0xe1,0,0);
  return *(undefined *)(param_1 + 0xc);
}



// === FUN_00023958 @ 0x23958 ===

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * FUN_00023958(undefined4 *param_1)

{
  uint uVar1;
  
  uVar1 = _DAT_fff602e4;
  *param_1 = _DAT_fff60020;
  if ((uint)param_1[2] <= uVar1) {
    param_1[2] = _DAT_fff602e8;
  }
  return param_1;
}



// === FUN_00023970 @ 0x23970 ===

int FUN_00023970(int param_1,undefined param_2,undefined param_3,undefined4 param_4)

{
  *(undefined *)(param_1 + 0xd) = 0x20;
  *(undefined *)(param_1 + 0x19) = 0;
  *(undefined *)(param_1 + 0x1a) = 0;
  *(undefined *)(param_1 + 0x1e) = 0;
  *(undefined *)(param_1 + 4) = param_2;
  *(undefined *)(param_1 + 5) = param_3;
  *(undefined4 *)(param_1 + 8) = param_4;
  *(undefined2 *)(param_1 + 0x1c) = 0x105;
  *(undefined4 *)(param_1 + 0x24) = 5;
  FUN_00023958(param_1);
  return param_1;
}



// === FUN_000239a0 @ 0x239a0 ===

undefined4 FUN_000239a0(undefined4 param_1,byte param_2)

{
  if (0x7c < param_2) {
    param_2 = 0x7d;
  }
  FUN_000238fc(param_1,5,param_2);
  return param_1;
}



// === FUN_000239b8 @ 0x239b8 ===

int FUN_000239b8(int param_1,byte param_2)

{
  int iVar1;
  int iVar2;
  byte bVar3;
  
  bVar3 = 1;
  if ((param_2 != 0) && (bVar3 = param_2, 0x1f < param_2)) {
    bVar3 = 0x20;
  }
  *(byte *)(param_1 + 0xd) = bVar3;
  iVar1 = 0x11;
  do {
    iVar2 = iVar1 + 1;
    FUN_000238fc(param_1,iVar1,*(undefined *)(param_1 + 0xd));
    iVar1 = iVar2;
  } while (iVar2 != 0x17);
  return param_1;
}



// === FUN_000239e8 @ 0x239e8 ===

bool FUN_000239e8(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_00023894(param_1,3);
  return *(byte *)(param_1 + 0x1c) - 2 == iVar1;
}



// === FUN_00023a0c @ 0x23a0c ===

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_00023a0c(int param_1)

{
  int iVar1;
  
  iVar1 = (*_DAT_fff602ec)(param_1);
  if (iVar1 != 0) {
    if (*(char *)(param_1 + 5) != *(char *)(param_1 + 4)) {
      FUN_00026c3c(*(char *)(param_1 + 4),3);
      FUN_00026c3c(*(undefined *)(param_1 + 5),3);
    }
    FUN_00023814(param_1,0);
    FUN_00023800(param_1,1);
  }
  return iVar1;
}



// === FUN_00023a48 @ 0x23a48 ===

int FUN_00023a48(int param_1)

{
  undefined uVar1;
  byte bVar2;
  
  FUN_00023814(param_1,0);
  FUN_000271d4(*(undefined4 *)(param_1 + 0x20),0);
  if (*(char *)(param_1 + 0x1b) != '\0') {
    FUN_00023940(param_1,0);
  }
  bVar2 = *(byte *)(param_1 + 0x18) & 0xfe;
  *(byte *)(param_1 + 0x18) = bVar2;
  FUN_000238fc(param_1,0,bVar2);
  uVar1 = *(undefined *)(param_1 + 0x1c);
  FUN_000238c0(param_1,10,param_1 + 0x13,uVar1);
  bVar2 = FUN_00023894(param_1,2,param_1 + 0x13,uVar1);
  FUN_000238fc(param_1,2,bVar2 | 1,uVar1);
  return param_1;
}



// === FUN_00023aa0 @ 0x23aa0 ===

int FUN_00023aa0(int param_1)

{
  byte bVar1;
  
  FUN_00023814(param_1,0);
  bVar1 = *(byte *)(param_1 + 0x18) & 0xfd;
  *(byte *)(param_1 + 0x18) = bVar1;
  FUN_000238fc(param_1,0,bVar1);
  return param_1;
}



// === FUN_00023ac4 @ 0x23ac4 ===

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_00023ac4(int param_1)

{
  byte bVar1;
  byte bVar2;
  
  bVar1 = *(byte *)(param_1 + 0x18);
  if ((bVar1 & 2) == 0) {
    bVar2 = bVar1 | 2;
    *(byte *)(param_1 + 0x18) = bVar2;
    FUN_000238fc(param_1,bVar1 & 2,bVar2);
    FUN_000271d4(_DAT_fff602f0,bVar1 & 2,bVar2);
  }
  return param_1;
}



// === FUN_00023ae8 @ 0x23ae8 ===

undefined4 FUN_00023ae8(undefined4 param_1)

{
  FUN_00023814(param_1,0);
  FUN_000238fc(param_1,7,0x10);
  FUN_00023858(param_1,0xe3,0,0);
  FUN_00023814(param_1,1,0,0);
  return param_1;
}



// === FUN_00023b10 @ 0x23b10 ===

int FUN_00023b10(int param_1,char param_2)

{
  byte bVar1;
  
  if ((byte)(param_2 - 2U) == 0) {
    FUN_000238fc(param_1,3,0);
    *(undefined *)(param_1 + 0x1c) = 2;
  }
  else {
    bVar1 = param_2 - 2U & 3;
    FUN_000238fc(param_1,3,bVar1);
    *(byte *)(param_1 + 0x1c) = bVar1 + 2;
  }
  return param_1;
}



// === FUN_00023b44 @ 0x23b44 ===

undefined4 * FUN_00023b44(undefined4 *param_1)

{
  undefined uVar1;
  
  FUN_00023828(param_1);
  uVar1 = FUN_00024064(*param_1,0x50);
  *(undefined *)(param_1 + 3) = uVar1;
  FUN_00024064(*param_1,0x73);
  FUN_00023844(param_1,0x73);
  return param_1;
}



// === FUN_00023b68 @ 0x23b68 ===

int FUN_00023b68(int param_1)

{
  uint uVar1;
  
  if (*(char *)(param_1 + 0x1b) != '\0') {
    uVar1 = FUN_00023894(param_1,0x1d);
    FUN_000238fc(param_1,0x1d,uVar1 & 0xfd);
    *(undefined *)(param_1 + 0x1b) = 0;
  }
  return param_1;
}



// === FUN_00023b8c @ 0x23b8c ===

int FUN_00023b8c(int param_1,char param_2)

{
  if (param_2 == '\0') {
    FUN_000238fc(param_1,1,0);
    if (*(char *)(param_1 + 0x1b) != '\0') {
      FUN_00023b68(param_1,1,0);
    }
  }
  else {
    FUN_000238fc(param_1,1,0x3f);
  }
  return param_1;
}



// === FUN_00023bbc @ 0x23bbc ===

undefined4 FUN_00023bbc(undefined4 param_1,byte param_2,char param_3)

{
  byte bVar1;
  
  bVar1 = FUN_00023894(param_1,6);
  if (2 < param_2) {
    param_2 = 3;
  }
  FUN_000238fc(param_1,6,bVar1 & 0xf8 | param_3 + param_2 * '\x02');
  return param_1;
}



// === FUN_00023bf0 @ 0x23bf0 ===

bool FUN_00023bf0(int param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = FUN_00023894(param_1,6);
  if (param_2 == 2) {
    *(undefined4 *)(param_1 + 0x20) = 0x1f9;
    uVar1 = 0x20;
  }
  else if (param_2 == 1) {
    *(undefined4 *)(param_1 + 0x20) = 0xf0;
    uVar1 = 8;
  }
  else {
    *(undefined4 *)(param_1 + 0x20) = 0x118;
    uVar1 = 0;
  }
  uVar1 = uVar2 & 0xd7 | uVar1;
  FUN_000238fc(param_1,6,uVar1);
  uVar2 = FUN_00023894(param_1,6,uVar1);
  return uVar1 == uVar2;
}



// === FUN_00023c44 @ 0x23c44 ===

bool FUN_00023c44(int param_1)

{
  undefined uVar1;
  int iVar2;
  int iVar3;
  
  FUN_000271c8(5);
  FUN_000238fc(param_1,4,0x5f);
  FUN_00023bf0(param_1,0,0x5f);
  iVar2 = FUN_00023894(param_1,0x1d,0x5f);
  FUN_00023b44(param_1,0x1d,0x5f);
  iVar3 = FUN_00023894(param_1,0x1d,0x5f);
  *(bool *)(param_1 + 0x19) = iVar2 == iVar3;
  if (iVar3 != 0) {
    if (iVar2 == iVar3) {
      FUN_00023b44(param_1,1,0x5f);
    }
    FUN_000238fc(param_1,0x1d,0);
  }
  *(undefined *)(param_1 + 0x1b) = 0;
  FUN_000238fc(param_1,0x1c,0);
  *(undefined *)(param_1 + 0x1d) = 0;
  FUN_000238fc(param_1,1,0x3f);
  FUN_000238fc(param_1,2,3);
  FUN_000239b8(param_1,0x20,3);
  FUN_00023b10(param_1,5,3);
  FUN_000239a0(param_1,0x4c,3);
  FUN_000238fc(param_1,7,0x70);
  FUN_00023928(param_1,7,0x70);
  FUN_00023940(param_1,7,0x70);
  FUN_000238fc(param_1,0,0xc);
  uVar1 = FUN_00023894(param_1,0,0xc);
  *(undefined *)(param_1 + 0x18) = uVar1;
  FUN_00023ac4(param_1,0,0xc);
  return *(char *)(param_1 + 0x18) == '\x0e';
}



// === FUN_00023d10 @ 0x23d10 ===

int FUN_00023d10(undefined4 *param_1,undefined4 param_2)

{
  int iVar1;
  
  *param_1 = param_2;
  iVar1 = FUN_00023a0c(param_1);
  if (iVar1 != 0) {
    iVar1 = FUN_00023c44(param_1);
  }
  return iVar1;
}



// === FUN_00023d28 @ 0x23d28 ===

int FUN_00023d28(int param_1,int param_2)

{
  byte bVar1;
  byte bVar2;
  
  bVar2 = *(byte *)(param_1 + 0x18) & 0xf3;
  if (param_2 != 0) {
    if (param_2 == 1) {
      bVar1 = 8;
    }
    else {
      bVar1 = 0xc;
    }
    bVar2 = bVar2 | bVar1;
  }
  *(byte *)(param_1 + 0x18) = bVar2;
  FUN_000238fc(param_1,0,*(undefined *)(param_1 + 0x18));
  return param_1;
}



// === FUN_00023d5c @ 0x23d5c ===

int FUN_00023d5c(int param_1)

{
  byte bVar1;
  
  bVar1 = *(byte *)(param_1 + 0x18) & 0xf7;
  *(byte *)(param_1 + 0x18) = bVar1;
  FUN_000238fc(param_1,0,bVar1);
  return param_1;
}

