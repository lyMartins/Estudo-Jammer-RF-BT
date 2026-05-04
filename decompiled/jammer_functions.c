// === FUN_000b2f5c @ 000b2f5c ===

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int * FUN_000b2f5c(int *param_1,char param_2,char param_3)

{
  byte bVar1;
  int *piVar2;
  int iVar3;
  uint *puVar4;
  uint uVar5;
  char cVar6;
  int iVar7;
  undefined4 uVar8;
  undefined uVar9;
  int iVar10;
  undefined auStack_30 [2];
  undefined2 uStack_2e;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  
  iVar7 = _DAT_fffd110c;
  if (param_3 == '\0') {
    if (*(char *)((int)param_1 + 0x12) == '\x06') {
      *(undefined *)((int)param_1 + 0x12) = 0;
      memw();
      iVar7 = *param_1;
      if (param_2 == '\0') {
        uVar9 = 9;
        if (iVar7 == 0) {
          memw();
          FUN_00079564(6,_DAT_fffd39e8,1,_DAT_ffff2f4c,_DAT_fffd158c,_DAT_ffff2f48,0x40a);
          do {
                    /* WARNING: Do nothing block with infinite loop */
          } while( true );
        }
      }
      else {
        uVar9 = 10;
      }
      *(undefined *)((int)param_1 + 0x13) = uVar9;
      memw();
      puVar4 = *(uint **)(iVar7 + 0x2c);
      if ((*puVar4 >> 0x15 & 1) != 0) {
        cVar6 = *(char *)((int)puVar4 + 5) + '\x02';
        memw();
        FUN_00093fdc(puVar4[4] >> 0x14 & 0xf,cVar6);
        piVar2 = *(int **)(iVar7 + 0x2c);
        FUN_000b3e54((uint)piVar2[4] >> 0x14 & 0xf,cVar6);
        return piVar2;
      }
      if ((*puVar4 >> 0x16 & 1) != 0) {
        FUN_00094be0(iVar7,1);
        return param_1;
      }
      uVar8 = 2;
      if ((*(byte *)((int)puVar4 + 6) < *(byte *)(_DAT_fffd110c + 0x15)) &&
         (uVar8 = 4, *(byte *)(_DAT_fffd110c + 0x14) <= *(byte *)((int)puVar4 + 7))) {
        uVar8 = 3;
      }
      FUN_00091410(param_1,iVar7,uVar8,1);
      return param_1;
    }
    if (*(char *)((int)param_1 + 0x12) != '\x05') {
      memw();
      FUN_00079564(6,_DAT_fffd39e8,1,_DAT_ffff2f54,_DAT_fffd158c,_DAT_ffff2f48,1099);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    iVar7 = *param_1;
    *(undefined *)((int)param_1 + 0x12) = 0;
    memw();
    if (iVar7 == 0) {
      memw();
      FUN_00079564(6,_DAT_fffd39e8,1,_DAT_ffff2f50,_DAT_fffd158c,_DAT_ffff2f48,0x42a);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    if ((**(uint **)(iVar7 + 0x2c) >> 0x13 & 1) == 0) {
      if ((**(uint **)(iVar7 + 0x2c) >> 0x16 & 1) == 0) {
        *(undefined *)((int)param_1 + 0x13) = 3;
        memw();
        memw();
        FUN_000b2f24(param_1,iVar7,1);
        return param_1;
      }
      *(undefined *)((int)param_1 + 0x13) = 2;
      memw();
      memw();
      iVar7 = FUN_000b4b88(*(undefined4 *)(iVar7 + 0x24),iVar7);
      if (iVar7 != 0) {
        piVar2 = *(int **)(*param_1 + 0x2c);
        FUN_00093eb8(piVar2[1] & 0xf,(uint)piVar2[4] >> 0x14 & 0xf);
        return piVar2;
      }
      FUN_00094c48(*param_1,1);
      return param_1;
    }
    (*_DAT_fffd6144)(auStack_30,0,0xc);
    FUN_000b4aa8(*(undefined *)(param_1 + 1),auStack_30,0xc);
    puVar4 = *(uint **)(*param_1 + 0x2c);
    uVar5 = puVar4[4];
    if ((*puVar4 & _DAT_fffbbeb8) == 0) {
      iVar7 = *_DAT_fffd1130;
      uVar9 = FUN_000b4b30(*(undefined *)(param_1 + 1),auStack_30,0xc);
      *(undefined *)(iVar7 + (uVar5 >> 0x14 & 0xf) * 0x30 + 0x4d) = uVar9;
      memw();
      uVar5 = *(uint *)(*(int *)(*param_1 + 0x2c) + 0x10);
      memw();
      cVar6 = '\0';
    }
    else {
      cVar6 = *(char *)((int)puVar4 + 5) + '\x01';
    }
    FUN_00093ffc(uVar5 >> 0x14 & 0xf,uStack_2e,uStack_2c,uStack_28,cVar6);
    uVar9 = 1;
    FUN_000b3e54(*(uint *)(*(int *)(*param_1 + 0x2c) + 0x10) >> 0x14 & 0xf,uStack_2e,uStack_2c,
                 uStack_28,cVar6);
  }
  else {
    if (1 < (byte)(*(char *)((int)param_1 + 0x12) - 1U)) {
      memw();
      FUN_00079564(6,_DAT_fffd39e8,1,_DAT_ffff2f58,_DAT_fffd158c,_DAT_ffff2f48,0x44e);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    if (param_2 == '\0') {
      *(undefined *)((int)param_1 + 0x12) = 3;
      memw();
      memw();
      FUN_000914f0(param_1,0);
      uVar9 = 5;
    }
    else {
      iVar3 = *param_1;
      if ((**(uint **)(iVar3 + 0x2c) >> 0x16 & 1) != 0) {
        bVar1 = *(byte *)((int)*(uint **)(iVar3 + 0x2c) + 5);
        if ((*(byte *)(_DAT_fffd110c + 0x2b) <= bVar1) &&
           ((iVar10 = FUN_00091110(iVar3,param_2), iVar10 != 0 || (*(byte *)(iVar7 + 0x2c) <= bVar1)
            ))) {
          FUN_000913a0(param_1,iVar3);
          return param_1;
        }
      }
      *(undefined *)((int)param_1 + 0x12) = 3;
      memw();
      memw();
      FUN_000914f0(param_1,0);
      uVar9 = 7;
    }
  }
  *(undefined *)((int)param_1 + 0x13) = uVar9;
  memw();
  memw();
  return param_1;
}



// === FUN_000571f8 @ 000571f8 ===

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_000571f8(byte *param_1,uint param_2)

{
  undefined uVar1;
  int *piVar2;
  code *pcVar3;
  uint uVar4;
  int iVar5;
  byte *pbVar6;
  int *piVar7;
  bool bVar8;
  byte *pbVar9;
  undefined4 unaff_a13;
  uint uVar10;
  undefined *puVar11;
  int iVar12;
  undefined4 uVar13;
  
  piVar2 = _DAT_fff91f00;
  param_2 = param_2 & 0xffff;
  uVar4 = param_2 >> 8;
  piVar7 = (int *)(_DAT_fff94c18 + uVar4 * 4);
  iVar5 = *piVar7;
  uVar10 = (**(code **)(*_DAT_fff91f00 + 0x10c))(param_2);
  if (uVar10 != 0x18) {
    if (uVar10 < 0x19) {
      if (uVar10 == 0) {
        return 0;
      }
    }
    else if (uVar10 < 0x1d) {
      return 0;
    }
    pcVar3 = *(code **)(*_DAT_fff91d44 + 0x1c);
    uVar13 = (**(code **)(*piVar2 + 0x10c))(param_2);
    (*pcVar3)(uVar13,0,_DAT_fff95ce0,0x70c);
    return 0;
  }
  *(byte *)(iVar5 + 0x41) = *param_1 & 1;
  memw();
  (**(code **)(*piVar2 + 0x128))(0x505,param_2);
  if (2 < param_1[2]) {
    uVar1 = *(undefined *)(iVar5 + 0x41);
    (**(code **)(*_DAT_fff91efc + 0x218))(uVar4,4,0x1e,uVar1);
    (**(code **)(*piVar2 + 0x108))(param_2,*(undefined *)(*piVar7 + 0x352),0x1e,uVar1);
    return 0;
  }
  pbVar6 = param_1 + 4;
  (*_DAT_fff61d40)((uint)param_1[2] * 8 + iVar5 + 100,pbVar6,8);
  pbVar9 = (byte *)(uint)*(byte *)(iVar5 + 0x56);
  if (pbVar9 == (byte *)0x0) {
    if ((*(char *)(iVar5 + 0x2f4) != '\0') && (param_1[2] == 1)) {
      unaff_a13 = 0xe;
      iVar12 = (**(code **)(*piVar2 + 0xc0))(_DAT_fff93a50,0,0x3d,0xe);
      (*_DAT_fff61d40)(iVar12,iVar5 + 0x82,6,0xe);
      (*_DAT_fff61d40)(iVar12 + 6,pbVar6,8,0xe);
      (**(code **)(*_DAT_fff91efc + 0x170))(iVar12,pbVar6,8,0xe);
      pbVar9 = pbVar6;
    }
  }
  else if (*(char *)(iVar5 + 0x2f6) != '\0') {
    unaff_a13 = 0xe;
    puVar11 = (undefined *)(**(code **)(*piVar2 + 0xc0))(_DAT_fff93a50,0,0x23,0xe);
    (*_DAT_fff61d40)(puVar11 + 6,pbVar6,8,0xe);
    *puVar11 = 0;
    memw();
    puVar11[4] = param_1[2];
    memw();
    puVar11[5] = param_1[3];
    piVar7 = _DAT_fff91efc;
    memw();
    *(short *)(puVar11 + 2) = (short)(param_2 >> 8) + 0x80;
    memw();
    (**(code **)(*piVar7 + 0x170))(puVar11,pbVar6,8,0xe);
    *(undefined *)(iVar5 + 0x2f6) = 0;
    memw();
    pbVar9 = pbVar6;
  }
  piVar7 = _DAT_fff91efc;
  if (((param_1[2] < param_1[3]) && (param_1[2] < 2)) &&
     (iVar12 = (**(code **)(*_DAT_fff91efc + 0x2c4))(param_2,pbVar9,8,unaff_a13), iVar12 == 0)) {
    (**(code **)(*piVar7 + 0x450))(param_2,uVar4,2,unaff_a13);
    return 0;
  }
  uVar1 = *(undefined *)(*(int *)(_DAT_fff94c18 + uVar4 * 4) + 0x352);
  (**(code **)(*piVar2 + 0x108))(param_2,uVar1,8,unaff_a13);
  iVar12 = (**(code **)(*piVar7 + 0xa9c))(*(code **)(*piVar7 + 0xa9c),uVar1,8,unaff_a13);
  if (((iVar12 != 0) &&
      (iVar12 = (**(code **)(*piVar7 + 0xa98))(*(code **)(*piVar7 + 0xa98),uVar1,8,unaff_a13),
      iVar12 != 0)) &&
     (iVar12 = (**(code **)(*piVar7 + 0x510))(iVar5 + 100,0x33,8,unaff_a13), iVar12 != 0)) {
    iVar12 = (**(code **)(*piVar7 + 0x510))(iVar5 + 0x6c,0x40,8,unaff_a13);
    if ((iVar12 != 0) &&
       (iVar12 = (**(code **)(*piVar7 + 0x510))(iVar5 + 0x74,0x88,8,unaff_a13), iVar12 != 0)) {
      iVar12 = (**(code **)(*piVar7 + 0x510))(iVar5 + 0x6c,0x43,8,unaff_a13);
      bVar8 = iVar12 != 0;
      goto LAB_00057443;
    }
  }
  bVar8 = false;
LAB_00057443:
  *(bool *)(iVar5 + 0x2e8) = bVar8;
  memw();
  return 0;
}

