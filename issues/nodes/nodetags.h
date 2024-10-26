/*-------------------------------------------------------------------------
 *
 * nodetags.h
 *    Generated node infrastructure code
 *
 * Portions Copyright (c) 1996-2024, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * NOTES
 *  ******************************
 *  *** DO NOT EDIT THIS FILE! ***
 *  ******************************
 *
 *  It has been GENERATED by src/backend/nodes/gen_node_support.pl
 *
 *-------------------------------------------------------------------------
 */
	T_List = 1,
	T_Alias = 2,
	T_RangeVar = 3,
	T_TableFunc = 4,
	T_IntoClause = 5,
	T_Var = 6,
	T_Const = 7,
	T_Param = 8,
	T_Aggref = 9,
	T_GroupingFunc = 10,
	T_WindowFunc = 11,
	T_SubscriptingRef = 12,
	T_FuncExpr = 13,
	T_NamedArgExpr = 14,
	T_OpExpr = 15,
	T_DistinctExpr = 16,
	T_NullIfExpr = 17,
	T_ScalarArrayOpExpr = 18,
	T_BoolExpr = 19,
	T_SubLink = 20,
	T_SubPlan = 21,
	T_AlternativeSubPlan = 22,
	T_FieldSelect = 23,
	T_FieldStore = 24,
	T_RelabelType = 25,
	T_CoerceViaIO = 26,
	T_ArrayCoerceExpr = 27,
	T_ConvertRowtypeExpr = 28,
	T_CollateExpr = 29,
	T_CaseExpr = 30,
	T_CaseWhen = 31,
	T_CaseTestExpr = 32,
	T_ArrayExpr = 33,
	T_RowExpr = 34,
	T_RowCompareExpr = 35,
	T_CoalesceExpr = 36,
	T_MinMaxExpr = 37,
	T_SQLValueFunction = 38,
	T_XmlExpr = 39,
	T_JsonFormat = 40,
	T_JsonReturning = 41,
	T_JsonValueExpr = 42,
	T_JsonConstructorExpr = 43,
	T_JsonIsPredicate = 44,
	T_NullTest = 45,
	T_BooleanTest = 46,
	T_MergeAction = 47,
	T_CoerceToDomain = 48,
	T_CoerceToDomainValue = 49,
	T_SetToDefault = 50,
	T_CurrentOfExpr = 51,
	T_NextValueExpr = 52,
	T_InferenceElem = 53,
	T_TargetEntry = 54,
	T_RangeTblRef = 55,
	T_JoinExpr = 56,
	T_FromExpr = 57,
	T_OnConflictExpr = 58,
	T_Query = 59,
	T_TypeName = 60,
	T_ColumnRef = 61,
	T_ParamRef = 62,
	T_A_Expr = 63,
	T_A_Const = 64,
	T_TypeCast = 65,
	T_CollateClause = 66,
	T_RoleSpec = 67,
	T_FuncCall = 68,
	T_A_Star = 69,
	T_A_Indices = 70,
	T_A_Indirection = 71,
	T_A_ArrayExpr = 72,
	T_ResTarget = 73,
	T_MultiAssignRef = 74,
	T_SortBy = 75,
	T_WindowDef = 76,
	T_RangeSubselect = 77,
	T_RangeFunction = 78,
	T_RangeTableFunc = 79,
	T_RangeTableFuncCol = 80,
	T_RangeTableSample = 81,
	T_ColumnDef = 82,
	T_TableLikeClause = 83,
	T_IndexElem = 84,
	T_DefElem = 85,
	T_LockingClause = 86,
	T_XmlSerialize = 87,
	T_PartitionElem = 88,
	T_PartitionSpec = 89,
	T_PartitionBoundSpec = 90,
	T_PartitionRangeDatum = 91,
	T_PartitionCmd = 92,
	T_RangeTblEntry = 93,
	T_RTEPermissionInfo = 94,
	T_RangeTblFunction = 95,
	T_TableSampleClause = 96,
	T_WithCheckOption = 97,
	T_SortGroupClause = 98,
	T_GroupingSet = 99,
	T_WindowClause = 100,
	T_RowMarkClause = 101,
	T_WithClause = 102,
	T_InferClause = 103,
	T_OnConflictClause = 104,
	T_CTESearchClause = 105,
	T_CTECycleClause = 106,
	T_CommonTableExpr = 107,
	T_MergeWhenClause = 108,
	T_TriggerTransition = 109,
	T_JsonOutput = 110,
	T_JsonKeyValue = 111,
	T_JsonParseExpr = 112,
	T_JsonScalarExpr = 113,
	T_JsonSerializeExpr = 114,
	T_JsonObjectConstructor = 115,
	T_JsonArrayConstructor = 116,
	T_JsonArrayQueryConstructor = 117,
	T_JsonAggConstructor = 118,
	T_JsonObjectAgg = 119,
	T_JsonArrayAgg = 120,
	T_RawStmt = 121,
	T_InsertStmt = 122,
	T_DeleteStmt = 123,
	T_UpdateStmt = 124,
	T_MergeStmt = 125,
	T_SelectStmt = 126,
	T_SetOperationStmt = 127,
	T_ReturnStmt = 128,
	T_PLAssignStmt = 129,
	T_CreateSchemaStmt = 130,
	T_AlterTableStmt = 131,
	T_ReplicaIdentityStmt = 132,
	T_AlterTableCmd = 133,
	T_AlterCollationStmt = 134,
	T_AlterDomainStmt = 135,
	T_GrantStmt = 136,
	T_ObjectWithArgs = 137,
	T_AccessPriv = 138,
	T_GrantRoleStmt = 139,
	T_AlterDefaultPrivilegesStmt = 140,
	T_CopyStmt = 141,
	T_VariableSetStmt = 142,
	T_VariableShowStmt = 143,
	T_CreateStmt = 144,
	T_Constraint = 145,
	T_CreateTableSpaceStmt = 146,
	T_DropTableSpaceStmt = 147,
	T_AlterTableSpaceOptionsStmt = 148,
	T_AlterTableMoveAllStmt = 149,
	T_CreateExtensionStmt = 150,
	T_AlterExtensionStmt = 151,
	T_AlterExtensionContentsStmt = 152,
	T_CreateFdwStmt = 153,
	T_AlterFdwStmt = 154,
	T_CreateForeignServerStmt = 155,
	T_AlterForeignServerStmt = 156,
	T_CreateForeignTableStmt = 157,
	T_CreateUserMappingStmt = 158,
	T_AlterUserMappingStmt = 159,
	T_DropUserMappingStmt = 160,
	T_ImportForeignSchemaStmt = 161,
	T_CreatePolicyStmt = 162,
	T_AlterPolicyStmt = 163,
	T_CreateAmStmt = 164,
	T_CreateTrigStmt = 165,
	T_CreateEventTrigStmt = 166,
	T_AlterEventTrigStmt = 167,
	T_CreatePLangStmt = 168,
	T_CreateRoleStmt = 169,
	T_AlterRoleStmt = 170,
	T_AlterRoleSetStmt = 171,
	T_DropRoleStmt = 172,
	T_CreateSeqStmt = 173,
	T_AlterSeqStmt = 174,
	T_DefineStmt = 175,
	T_CreateDomainStmt = 176,
	T_CreateOpClassStmt = 177,
	T_CreateOpClassItem = 178,
	T_CreateOpFamilyStmt = 179,
	T_AlterOpFamilyStmt = 180,
	T_DropStmt = 181,
	T_TruncateStmt = 182,
	T_CommentStmt = 183,
	T_SecLabelStmt = 184,
	T_DeclareCursorStmt = 185,
	T_ClosePortalStmt = 186,
	T_FetchStmt = 187,
	T_IndexStmt = 188,
	T_CreateStatsStmt = 189,
	T_StatsElem = 190,
	T_AlterStatsStmt = 191,
	T_CreateFunctionStmt = 192,
	T_FunctionParameter = 193,
	T_AlterFunctionStmt = 194,
	T_DoStmt = 195,
	T_InlineCodeBlock = 196,
	T_CallStmt = 197,
	T_CallContext = 198,
	T_RenameStmt = 199,
	T_AlterObjectDependsStmt = 200,
	T_AlterObjectSchemaStmt = 201,
	T_AlterOwnerStmt = 202,
	T_AlterOperatorStmt = 203,
	T_AlterTypeStmt = 204,
	T_RuleStmt = 205,
	T_NotifyStmt = 206,
	T_ListenStmt = 207,
	T_UnlistenStmt = 208,
	T_TransactionStmt = 209,
	T_CompositeTypeStmt = 210,
	T_CreateEnumStmt = 211,
	T_CreateRangeStmt = 212,
	T_AlterEnumStmt = 213,
	T_ViewStmt = 214,
	T_LoadStmt = 215,
	T_CreatedbStmt = 216,
	T_AlterDatabaseStmt = 217,
	T_AlterDatabaseRefreshCollStmt = 218,
	T_AlterDatabaseSetStmt = 219,
	T_DropdbStmt = 220,
	T_AlterSystemStmt = 221,
	T_ClusterStmt = 222,
	T_VacuumStmt = 223,
	T_VacuumRelation = 224,
	T_ExplainStmt = 225,
	T_CreateTableAsStmt = 226,
	T_RefreshMatViewStmt = 227,
	T_CheckPointStmt = 228,
	T_DiscardStmt = 229,
	T_LockStmt = 230,
	T_ConstraintsSetStmt = 231,
	T_ReindexStmt = 232,
	T_CreateConversionStmt = 233,
	T_CreateCastStmt = 234,
	T_CreateTransformStmt = 235,
	T_PrepareStmt = 236,
	T_ExecuteStmt = 237,
	T_DeallocateStmt = 238,
	T_DropOwnedStmt = 239,
	T_ReassignOwnedStmt = 240,
	T_AlterTSDictionaryStmt = 241,
	T_AlterTSConfigurationStmt = 242,
	T_PublicationTable = 243,
	T_PublicationObjSpec = 244,
	T_CreatePublicationStmt = 245,
	T_AlterPublicationStmt = 246,
	T_CreateSubscriptionStmt = 247,
	T_AlterSubscriptionStmt = 248,
	T_DropSubscriptionStmt = 249,
	T_PlannerGlobal = 250,
	T_PlannerInfo = 251,
	T_RelOptInfo = 252,
	T_IndexOptInfo = 253,
	T_ForeignKeyOptInfo = 254,
	T_StatisticExtInfo = 255,
	T_JoinDomain = 256,
	T_EquivalenceClass = 257,
	T_EquivalenceMember = 258,
	T_PathKey = 259,
	T_PathKeyInfo = 260,
	T_PathTarget = 261,
	T_ParamPathInfo = 262,
	T_Path = 263,
	T_IndexPath = 264,
	T_IndexClause = 265,
	T_BitmapHeapPath = 266,
	T_BitmapAndPath = 267,
	T_BitmapOrPath = 268,
	T_TidPath = 269,
	T_TidRangePath = 270,
	T_SubqueryScanPath = 271,
	T_ForeignPath = 272,
	T_CustomPath = 273,
	T_AppendPath = 274,
	T_MergeAppendPath = 275,
	T_GroupResultPath = 276,
	T_MaterialPath = 277,
	T_MemoizePath = 278,
	T_UniquePath = 279,
	T_GatherPath = 280,
	T_GatherMergePath = 281,
	T_NestPath = 282,
	T_MergePath = 283,
	T_HashPath = 284,
	T_ProjectionPath = 285,
	T_ProjectSetPath = 286,
	T_SortPath = 287,
	T_IncrementalSortPath = 288,
	T_GroupPath = 289,
	T_UpperUniquePath = 290,
	T_AggPath = 291,
	T_GroupingSetData = 292,
	T_RollupData = 293,
	T_GroupingSetsPath = 294,
	T_MinMaxAggPath = 295,
	T_WindowAggPath = 296,
	T_SetOpPath = 297,
	T_RecursiveUnionPath = 298,
	T_LockRowsPath = 299,
	T_ModifyTablePath = 300,
	T_LimitPath = 301,
	T_RestrictInfo = 302,
	T_PlaceHolderVar = 303,
	T_SpecialJoinInfo = 304,
	T_OuterJoinClauseInfo = 305,
	T_AppendRelInfo = 306,
	T_RowIdentityVarInfo = 307,
	T_PlaceHolderInfo = 308,
	T_MinMaxAggInfo = 309,
	T_PlannerParamItem = 310,
	T_AggInfo = 311,
	T_AggTransInfo = 312,
	T_UniqueRelInfo = 313,
	T_PlannedStmt = 314,
	T_Result = 315,
	T_ProjectSet = 316,
	T_ModifyTable = 317,
	T_Append = 318,
	T_MergeAppend = 319,
	T_RecursiveUnion = 320,
	T_BitmapAnd = 321,
	T_BitmapOr = 322,
	T_SeqScan = 323,
	T_SampleScan = 324,
	T_IndexScan = 325,
	T_IndexOnlyScan = 326,
	T_BitmapIndexScan = 327,
	T_BitmapHeapScan = 328,
	T_TidScan = 329,
	T_TidRangeScan = 330,
	T_SubqueryScan = 331,
	T_FunctionScan = 332,
	T_ValuesScan = 333,
	T_TableFuncScan = 334,
	T_CteScan = 335,
	T_NamedTuplestoreScan = 336,
	T_WorkTableScan = 337,
	T_ForeignScan = 338,
	T_CustomScan = 339,
	T_NestLoop = 340,
	T_NestLoopParam = 341,
	T_MergeJoin = 342,
	T_HashJoin = 343,
	T_Material = 344,
	T_Memoize = 345,
	T_Sort = 346,
	T_IncrementalSort = 347,
	T_Group = 348,
	T_Agg = 349,
	T_WindowAgg = 350,
	T_Unique = 351,
	T_Gather = 352,
	T_GatherMerge = 353,
	T_Hash = 354,
	T_SetOp = 355,
	T_LockRows = 356,
	T_Limit = 357,
	T_PlanRowMark = 358,
	T_PartitionPruneInfo = 359,
	T_PartitionedRelPruneInfo = 360,
	T_PartitionPruneStepOp = 361,
	T_PartitionPruneStepCombine = 362,
	T_PlanInvalItem = 363,
	T_ExprState = 364,
	T_IndexInfo = 365,
	T_ExprContext = 366,
	T_ReturnSetInfo = 367,
	T_ProjectionInfo = 368,
	T_JunkFilter = 369,
	T_OnConflictSetState = 370,
	T_MergeActionState = 371,
	T_ResultRelInfo = 372,
	T_EState = 373,
	T_WindowFuncExprState = 374,
	T_SetExprState = 375,
	T_SubPlanState = 376,
	T_DomainConstraintState = 377,
	T_ResultState = 378,
	T_ProjectSetState = 379,
	T_ModifyTableState = 380,
	T_AppendState = 381,
	T_MergeAppendState = 382,
	T_RecursiveUnionState = 383,
	T_BitmapAndState = 384,
	T_BitmapOrState = 385,
	T_ScanState = 386,
	T_SeqScanState = 387,
	T_SampleScanState = 388,
	T_IndexScanState = 389,
	T_IndexOnlyScanState = 390,
	T_BitmapIndexScanState = 391,
	T_BitmapHeapScanState = 392,
	T_TidScanState = 393,
	T_TidRangeScanState = 394,
	T_SubqueryScanState = 395,
	T_FunctionScanState = 396,
	T_ValuesScanState = 397,
	T_TableFuncScanState = 398,
	T_CteScanState = 399,
	T_NamedTuplestoreScanState = 400,
	T_WorkTableScanState = 401,
	T_ForeignScanState = 402,
	T_CustomScanState = 403,
	T_JoinState = 404,
	T_NestLoopState = 405,
	T_MergeJoinState = 406,
	T_HashJoinState = 407,
	T_MaterialState = 408,
	T_MemoizeState = 409,
	T_SortState = 410,
	T_IncrementalSortState = 411,
	T_GroupState = 412,
	T_AggState = 413,
	T_WindowAggState = 414,
	T_UniqueState = 415,
	T_GatherState = 416,
	T_GatherMergeState = 417,
	T_HashState = 418,
	T_SetOpState = 419,
	T_LockRowsState = 420,
	T_LimitState = 421,
	T_IndexAmRoutine = 422,
	T_TableAmRoutine = 423,
	T_TsmRoutine = 424,
	T_EventTriggerData = 425,
	T_TriggerData = 426,
	T_TupleTableSlot = 427,
	T_FdwRoutine = 428,
	T_Bitmapset = 429,
	T_ExtensibleNode = 430,
	T_ErrorSaveContext = 431,
	T_IdentifySystemCmd = 432,
	T_BaseBackupCmd = 433,
	T_CreateReplicationSlotCmd = 434,
	T_DropReplicationSlotCmd = 435,
	T_AlterReplicationSlotCmd = 436,
	T_StartReplicationCmd = 437,
	T_ReadReplicationSlotCmd = 438,
	T_TimeLineHistoryCmd = 439,
	T_UploadManifestCmd = 440,
	T_SupportRequestSimplify = 441,
	T_SupportRequestSelectivity = 442,
	T_SupportRequestCost = 443,
	T_SupportRequestRows = 444,
	T_SupportRequestIndexCondition = 445,
	T_SupportRequestWFuncMonotonic = 446,
	T_SupportRequestOptimizeWindowClause = 447,
	T_Integer = 448,
	T_Float = 449,
	T_Boolean = 450,
	T_String = 451,
	T_BitString = 452,
	T_ForeignKeyCacheInfo = 453,
	T_IntList = 454,
	T_OidList = 455,
	T_XidList = 456,
	T_AllocSetContext = 457,
	T_GenerationContext = 458,
	T_SlabContext = 459,
	T_TIDBitmap = 460,
	T_WindowObjectData = 461,
