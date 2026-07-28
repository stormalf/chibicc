#include "chibicc.h"


static BuiltinEntry builtin_table[] = {
    { "__builtin_ia32_packssdw", ND_PACKSSDW },
    { "__builtin_ia32_packsswb", ND_PACKSSWB },
    { "__builtin_ia32_packuswb", ND_PACKUSWB },
    { "__builtin_ia32_punpckhbw", ND_PUNPCKHBW },
    { "__builtin_ia32_punpckhwd", ND_PUNPCKHWD },
    { "__builtin_ia32_punpckhdq", ND_PUNPCKHDQ },
    { "__builtin_ia32_punpcklbw", ND_PUNPCKLBW },
    { "__builtin_ia32_punpcklwd", ND_PUNPCKLWD },
    { "__builtin_ia32_punpckldq", ND_PUNPCKLDQ },
    { "__builtin_ia32_paddb", ND_PADDB },
    { "__builtin_ia32_paddw", ND_PADDW },
    { "__builtin_ia32_paddd", ND_PADDD },
    { "__builtin_ia32_paddq", ND_PADDQ },
    { "__builtin_ia32_paddsb", ND_PADDSB },
    { "__builtin_ia32_paddsw", ND_PADDSW },
    { "__builtin_ia32_paddusb", ND_PADDUSB },
    { "__builtin_ia32_paddusw", ND_PADDUSW },
    { "__builtin_ia32_psubb", ND_PSUBB },
    { "__builtin_ia32_psubw", ND_PSUBW },
    { "__builtin_ia32_psubd", ND_PSUBD },
    { "__builtin_ia32_psubq", ND_PSUBQ },
    { "__builtin_ia32_psubsb", ND_PSUBSB },
    { "__builtin_ia32_psubsw", ND_PSUBSW },
    { "__builtin_ia32_psubusb", ND_PSUBUSB },
    { "__builtin_ia32_psubusw", ND_PSUBUSW },
    { "__builtin_ia32_pmaddwd", ND_PMADDWD },
    { "__builtin_ia32_pmulhw", ND_PMULHW },
    { "__builtin_ia32_pmullw", ND_PMULLW },
    { "__builtin_ia32_psllw", ND_PSLLW },
    { "__builtin_ia32_psllwi", ND_PSLLWI },
    { "__builtin_ia32_pslld", ND_PSLLD },    
    { "__builtin_ia32_pslldi", ND_PSLLDI },
    { "__builtin_ia32_psllq", ND_PSLLQ },
    { "__builtin_ia32_psllqi", ND_PSLLQI },
    { "__builtin_ia32_psraw", ND_PSRAW },
    { "__builtin_ia32_psrawi", ND_PSRAWI },
    { "__builtin_ia32_psrad", ND_PSRAD },
    { "__builtin_ia32_psradi", ND_PSRADI },
    { "__builtin_ia32_psrlw", ND_PSRLW },
    { "__builtin_ia32_psrlwi", ND_PSRLWI },
    { "__builtin_ia32_psrld", ND_PSRLD },
    { "__builtin_ia32_psrldi", ND_PSRLDI },
    { "__builtin_ia32_psrlq", ND_PSRLQ },
    { "__builtin_ia32_psrlqi", ND_PSRLQI },
    { "__builtin_ia32_pand", ND_PAND },
    { "__builtin_ia32_pandn", ND_PANDN },
    { "__builtin_ia32_por", ND_POR },
    { "__builtin_ia32_pxor", ND_PXOR },
    { "__builtin_ia32_pcmpeqb", ND_PCMPEQB },
    { "__builtin_ia32_pcmpgtb", ND_PCMPGTB },
    { "__builtin_ia32_pcmpeqw", ND_PCMPEQW },
    { "__builtin_ia32_pcmpgtw", ND_PCMPGTW },
    { "__builtin_ia32_pcmpeqd", ND_PCMPEQD },    
    { "__builtin_ia32_pcmpgtd", ND_PCMPGTD },      
    { "__builtin_ia32_vec_init_v4hi", ND_VECINITV4HI },  
    { "__builtin_ia32_vec_init_v8qi", ND_VECINITV8QI },    
    { "__builtin_ia32_vec_init_v2si", ND_VECINITV2SI },       
    { "__builtin_ia32_vec_ext_v2si", ND_VECEXTV2SI },       
    { "__builtin_ia32_vec_ext_v4si", ND_VECEXTV4SI },
    { "__builtin_ia32_vec_ext_v4sf", ND_VECEXTV4SF },       
    { "__builtin_ia32_emms", ND_EMMS },       
    { "__builtin_ia32_sfence", ND_SFENCE },       
    { "__builtin_ia32_lfence", ND_LFENCE },     
    { "__builtin_ia32_mfence", ND_MFENCE },       
    { "__builtin_ia32_pause", ND_PAUSE },     
    { "__builtin_ia32_stmxcsr", ND_STMXCSR },   
    { "__builtin_ia32_ldmxcsr", ND_LDMXCSR },     
    { "__builtin_ia32_cvtpi2ps", ND_CVTPI2PS },    
    { "__builtin_ia32_cvtps2pi", ND_CVTPS2PI },    
    { "__builtin_ia32_addss", ND_ADDSS },        
    { "__builtin_ia32_subss", ND_SUBSS },        
    { "__builtin_ia32_mulss", ND_MULSS },   
    { "__builtin_ia32_divss", ND_DIVSS },     
    { "__builtin_ia32_sqrtss", ND_SQRTSS },   
    { "__builtin_ia32_sqrtps", ND_SQRTPS },   
    { "__builtin_ia32_rcpss", ND_RCPSS },     
    { "__builtin_ia32_rsqrtss", ND_RSQRTSS },
    { "__builtin_ia32_rsqrtps", ND_RSQRTPS },
    { "__builtin_ia32_minss", ND_MINSS },          
    { "__builtin_ia32_minps", ND_MINPS },           
    { "__builtin_ia32_maxss", ND_MAXSS },  
    { "__builtin_ia32_maxps", ND_MAXPS },       
    { "__builtin_ia32_rcpps", ND_RCPPS },     
    { "__builtin_ia32_andps", ND_ANDPS },      
    { "__builtin_ia32_andnps", ND_ANDNPS }, 
    { "__builtin_ia32_orps", ND_ORPS },   
    { "__builtin_ia32_xorps", ND_XORPS },  
    { "__builtin_ia32_cmpeqss", ND_CMPEQSS },
    { "__builtin_ia32_cmpltss", ND_CMPLTSS },       
    { "__builtin_ia32_cmpless", ND_CMPLESS },      
    { "__builtin_ia32_movss", ND_MOVSS },    
    { "__builtin_ia32_cmpneqss", ND_CMPNEQSS },  
    { "__builtin_ia32_cmpnltss", ND_CMPNLTSS },       
    { "__builtin_ia32_cmpnless", ND_CMPNLESS },         
    { "__builtin_ia32_cmpordss", ND_CMPORDSS },  
    { "__builtin_ia32_cmpunordss", ND_CMPUNORDSS },  
    { "__builtin_ia32_cmpeqps", ND_CMPEQPS },
    { "__builtin_ia32_cmpltps", ND_CMPLTPS },
    { "__builtin_ia32_cmpleps", ND_CMPLEPS },
    { "__builtin_ia32_cmpgtps", ND_CMPGTPS },
    { "__builtin_ia32_cmpgeps", ND_CMPGEPS },
    { "__builtin_ia32_cmpneqps", ND_CMPNEQPS },
    { "__builtin_ia32_cmpnltps", ND_CMPNLTPS },
    { "__builtin_ia32_cmpnleps", ND_CMPNLEPS },
    { "__builtin_ia32_cmpngtps", ND_CMPNGTPS },
    { "__builtin_ia32_cmpngeps", ND_CMPNGEPS },
    { "__builtin_ia32_cmpordps", ND_CMPORDPS },  
    { "__builtin_ia32_cmpunordps", ND_CMPUNORDPS },  
    { "__builtin_ia32_comieq", ND_COMIEQ },  
    { "__builtin_ia32_comilt", ND_COMILT },  
    { "__builtin_ia32_comile", ND_COMILE },  
    { "__builtin_ia32_comigt", ND_COMIGT },  
    { "__builtin_ia32_comige", ND_COMIGE },  
    { "__builtin_ia32_comineq", ND_COMINEQ },  
    { "__builtin_ia32_ucomieq", ND_UCOMIEQ },  
    { "__builtin_ia32_ucomilt", ND_UCOMILT },  
    { "__builtin_ia32_ucomile", ND_UCOMILE },  
    { "__builtin_ia32_ucomigt", ND_UCOMIGT },  
    { "__builtin_ia32_ucomige", ND_UCOMIGE },  
    { "__builtin_ia32_ucomineq", ND_UCOMINEQ },   
    { "__builtin_ia32_cvtss2si", ND_CVTSS2SI },   
    { "__builtin_ia32_cvtss2si64", ND_CVTSS2SI64 },   
    { "__builtin_ia32_cvttss2si", ND_CVTTSS2SI },   
    { "__builtin_ia32_cvttss2si64", ND_CVTTSS2SI64 },
    { "__builtin_ia32_cvttps2pi", ND_CVTTPS2PI },      
    { "__builtin_ia32_cvtsi2ss", ND_CVTSI2SS },      
    { "__builtin_ia32_cvtsi642ss", ND_CVTSI642SS },
    { "__builtin_ia32_movlhps", ND_MOVLHPS },         
    { "__builtin_ia32_movhlps", ND_MOVHLPS },         
    { "__builtin_ia32_unpckhps", ND_UNPCKHPS },    
    { "__builtin_ceil", ND_BUILTIN_CEIL },
    { "__builtin_floor", ND_BUILTIN_FLOOR },
    { "__builtin_ceilf", ND_BUILTIN_CEILF },
    { "__builtin_floorf", ND_BUILTIN_FLOORF },
    { "__builtin_ceill", ND_BUILTIN_CEILL },
    { "__builtin_floorl", ND_BUILTIN_FLOORL },
    { "__builtin_stdc_bit_ceil", ND_STDC_BIT_CEIL },

    { "__builtin_ia32_unpcklps", ND_UNPCKLPS },         
    { "__builtin_ia32_loadhps", ND_LOADHPS },   
    { "__builtin_ia32_storehps", ND_STOREHPS },        
    { "__builtin_ia32_loadlps", ND_LOADLPS },   
    { "__builtin_ia32_storelps", ND_STORELPS },   
    { "__builtin_ia32_movmskps", ND_MOVMSKPS },  
    { "__builtin_ia32_shufps", ND_SHUFPS },         
    { "__builtin_shuffle", ND_SHUFFLE },       
    { "__builtin_ia32_pmaxsw", ND_PMAXSW },     
    { "__builtin_ia32_pmaxub", ND_PMAXUB },   
    { "__builtin_ia32_pminsw", ND_PMINSW },   
    { "__builtin_ia32_pminub", ND_PMINUB },          
    { "__builtin_ia32_clflush", ND_CLFLUSH },          
    { "_mm_clflush", ND_CLFLUSH },          
    { "__builtin_ia32_pmovmskb", ND_PMOVMSKB },   
    { "__builtin_ia32_pmulhuw", ND_PMULHUW },
    { "__builtin_ia32_maskmovq", ND_MASKMOVQ },    
    { "__builtin_ia32_pavgb", ND_PAVGB },
    { "__builtin_ia32_pavgw", ND_PAVGW },
    { "__builtin_ia32_psadbw", ND_PSADBW },
    { "__builtin_ia32_movntq", ND_MOVNTQ },
    { "__builtin_ia32_movntps", ND_MOVNTPS },    
    { "__builtin_ia32_shufpd", ND_SHUFPD },    
    { "__builtin_ia32_roundpd", ND_ROUNDPD },    
    { "__builtin_ia32_roundsd", ND_ROUNDSD },  
    { "__builtin_ia32_roundss", ND_ROUNDSS },    
    { "__builtin_ia32_roundps", ND_ROUNDPS },    
    { "__builtin_ia32_addsd", ND_ADDSD },  
    { "__builtin_ia32_subsd", ND_SUBSD },  
    { "__builtin_ia32_mulsd", ND_MULSD },  
    { "__builtin_ia32_divsd", ND_DIVSD }, 
    { "__builtin_ia32_sqrtpd", ND_SQRTPD },
    { "__builtin_ia32_movsd", ND_MOVSD },  
    { "__builtin_ia32_sqrtsd", ND_SQRTSD },
    { "__builtin_ia32_minpd", ND_MINPD },      
    { "__builtin_ia32_minsd", ND_MINSD },      
    { "__builtin_ia32_maxpd", ND_MAXPD },        
    { "__builtin_ia32_maxsd", ND_MAXSD },       
    { "__builtin_ia32_andpd", ND_ANDPD }, 
    { "__builtin_ia32_andnpd", ND_ANDNPD },
    { "__builtin_ia32_orpd", ND_ORPD },      
    { "__builtin_ia32_xorpd", ND_XORPD },   
    { "__builtin_ia32_cmpeqpd", ND_CMPEQPD },  
    { "__builtin_ia32_cmpltpd", ND_CMPLTPD },  
    { "__builtin_ia32_cmplepd", ND_CMPLEPD },     
    { "__builtin_ia32_cmpgtpd", ND_CMPGTPD },     
    { "__builtin_ia32_cmpgepd", ND_CMPGEPD },    
    { "__builtin_ia32_cmpneqpd", ND_CMPNEQPD },        
    { "__builtin_ia32_cmpnltpd", ND_CMPNLTPD }, 
    { "__builtin_ia32_cmpnlepd", ND_CMPNLEPD }, 
    { "__builtin_ia32_cmpngtpd", ND_CMPNGTPD },  
    { "__builtin_ia32_cmpngepd", ND_CMPNGEPD },    
    { "__builtin_ia32_cmpordpd", ND_CMPORDPD },       
    { "__builtin_ia32_cmpunordpd", ND_CMPUNORDPD },   
    { "__builtin_ia32_cmpeqsd", ND_CMPEQSD },         
    { "__builtin_ia32_cmpltsd", ND_CMPLTSD },       
    { "__builtin_ia32_cmplesd", ND_CMPLESD }, 
    { "__builtin_ia32_cmpneqsd", ND_CMPNEQSD },     
    { "__builtin_ia32_cmpnltsd", ND_CMPNLTSD },    
    { "__builtin_ia32_cmpnlesd", ND_CMPNLESD },   
    { "__builtin_ia32_cmpordsd", ND_CMPORDSD },       
    { "__builtin_ia32_cmpunordsd", ND_CMPUNORDSD },     
    { "__builtin_ia32_comisdeq", ND_COMISDEQ },     
    { "__builtin_ia32_comisdlt", ND_COMISDLT},   
    { "__builtin_ia32_comisdle", ND_COMISDLE},   
    { "__builtin_ia32_comisdgt", ND_COMISDGT},   
    { "__builtin_ia32_comisdge", ND_COMISDGE},    
    { "__builtin_ia32_comisdneq", ND_COMISDNEQ},  
    { "__builtin_ia32_ucomisdeq", ND_UCOMISDEQ },     
    { "__builtin_ia32_ucomisdlt", ND_UCOMISDLT},   
    { "__builtin_ia32_ucomisdle", ND_UCOMISDLE},   
    { "__builtin_ia32_ucomisdgt", ND_UCOMISDGT},   
    { "__builtin_ia32_ucomisdge", ND_UCOMISDGE},    
    { "__builtin_ia32_ucomisdneq", ND_UCOMISDNEQ},    
    { "__builtin_ia32_movq128", ND_MOVQ128},     
    { "__builtin_ia32_cvtdq2pd", ND_CVTDQ2PD},     
    { "__builtin_ia32_cvtdq2ps", ND_CVTDQ2PS},     
    { "__builtin_ia32_cvtpd2dq", ND_CVTPD2DQ}, 
    { "__builtin_ia32_cvtpd2pi", ND_CVTPD2PI},  
    { "__builtin_ia32_cvtpd2ps", ND_CVTPD2PS},    
    { "__builtin_ia32_cvttpd2dq", ND_CVTTPD2DQ},
    { "__builtin_ia32_cvttpd2pi", ND_CVTTPD2PI},       
    { "__builtin_ia32_cvtpi2pd", ND_CVTPI2PD}, 
    { "__builtin_ia32_cvtps2dq", ND_CVTPS2DQ},  
    { "__builtin_ia32_cvttps2dq", ND_CVTTPS2DQ},
    { "__builtin_ia32_cvtps2pd", ND_CVTPS2PD},  
    { "__builtin_ia32_cvtsd2si", ND_CVTSD2SI},      
    { "__builtin_ia32_cvtsd2si64", ND_CVTSD2SI64}, 
    { "__builtin_ia32_cvttsd2si", ND_CVTTSD2SI},   
    { "__builtin_ia32_cvttsd2si64", ND_CVTTSD2SI64},
    { "__builtin_ia32_cvtsd2ss", ND_CVTSD2SS},        
    { "__builtin_ia32_cvtsi2sd", ND_CVTSI2SD},        
    { "__builtin_ia32_cvtsi642sd", ND_CVTSI642SD},
    { "__builtin_ia32_cvtss2sd", ND_CVTSS2SD},      
    { "__builtin_ia32_unpckhpd", ND_UNPCKHPD},           
    { "__builtin_ia32_unpcklpd", ND_UNPCKLPD},   
    { "__builtin_ia32_loadhpd", ND_LOADHPD },   
    { "__builtin_ia32_loadlpd", ND_LOADLPD },      
    { "__builtin_ia32_movmskpd", ND_MOVMSKPD },    
    { "__builtin_ia32_packsswb128", ND_PACKSSWB128 },  
    { "__builtin_ia32_packssdw128", ND_PACKSSDW128 },        
    { "__builtin_ia32_packuswb128", ND_PACKUSWB128 },       
    { "__builtin_ia32_punpckhbw128", ND_PUNPCKHBW128 },   
    { "__builtin_ia32_punpckhwd128", ND_PUNPCKHWD128 }, 
    { "__builtin_ia32_punpckhdq128", ND_PUNPCKHDQ128 },    
    { "__builtin_ia32_punpckhqdq128", ND_PUNPCKHQDQ128 },
    { "__builtin_ia32_punpcklbw128", ND_PUNPCKLBW128 },          
    { "__builtin_ia32_punpcklwd128", ND_PUNPCKLWD128 },    
    { "__builtin_ia32_punpckldq128", ND_PUNPCKLDQ128 }, 
    { "__builtin_ia32_punpcklqdq128", ND_PUNPCKLQDQ128 },        
    { "__builtin_ia32_paddsb128", ND_PADDSB128 },     
    { "__builtin_ia32_paddsw128", ND_PADDSW128 },   
    { "__builtin_ia32_paddusb128", ND_PADDUSB128 },     
    { "__builtin_ia32_paddusw128", ND_PADDUSW128 },       
    { "__builtin_ia32_psubsb128", ND_PSUBSB128 },     
    { "__builtin_ia32_psubsw128", ND_PSUBSW128 },   
    { "__builtin_ia32_psubusb128", ND_PSUBUSB128 },    
    { "__builtin_ia32_psubusw128", ND_PSUBUSW128 },              
    { "__builtin_ia32_pmaddwd128", ND_PMADDWD128 },  
    { "__builtin_ia32_pmaddwd256", ND_PMADDWD256 },  
    { "__builtin_ia32_pmulhw128", ND_PMULHW128 },      
    { "__builtin_ia32_pmuludq", ND_PMULUDQ },          
    { "__builtin_ia32_pmuludq128", ND_PMULUDQ128 },          
    { "__builtin_ia32_psllwi128", ND_PSLLWI128 },   
    { "__builtin_ia32_pslldi128", ND_PSLLDI128 },    
    { "__builtin_ia32_psllqi128", ND_PSLLQI128 },     
    { "__builtin_ia32_psrawi128", ND_PSRAWI128 },          
    { "__builtin_ia32_psrawi256", ND_PSRAWI256 },          
    { "__builtin_ia32_psradi128", ND_PSRADI128 },     
    { "__builtin_ia32_psrlwi128", ND_PSRLWI128 },    
    { "__builtin_ia32_psrlwi256", ND_PSRLWI256 },    
    { "__builtin_ia32_psrldi128", ND_PSRLDI128 },       
    { "__builtin_ia32_psrlqi128", ND_PSRLQI128 }, 
    { "__builtin_ia32_psllw128", ND_PSLLW128 },   
    { "__builtin_ia32_pslld128", ND_PSLLD128 },       
    { "__builtin_ia32_psllq128", ND_PSLLQ128 },        
    { "__builtin_ia32_psraw128", ND_PSRAW128 },   
    { "__builtin_ia32_psrad128", ND_PSRAD128 },  
    { "__builtin_ia32_psrlw128", ND_PSRLW128 },  
    { "__builtin_ia32_psrld128", ND_PSRLD128 },
    { "__builtin_ia32_psrlq128", ND_PSRLQ128 },        
    { "__builtin_ia32_pandn128", ND_PANDN128 },    
    { "__builtin_ia32_pmaxsw128", ND_PMAXSW128 },   
    { "__builtin_ia32_pmaxub128", ND_PMAXUB128 }, 
    { "__builtin_ia32_pminsw128", ND_PMINSW128 },   
    { "__builtin_ia32_pminub128", ND_PMINUB128 }, 
    { "__builtin_ia32_pmovmskb128", ND_PMOVMSKB128 },  
    { "__builtin_ia32_pmovmskb256", ND_PMOVMSKB256 },  
    { "__builtin_ia32_pmulhuw128", ND_PMULHUW128 }, 
    { "__builtin_ia32_maskmovdqu", ND_MASKMOVDQU },     
    { "__builtin_ia32_pavgb128", ND_PAVGB128 },   
    { "__builtin_ia32_pavgw128", ND_PAVGW128 },   
    { "__builtin_ia32_pavgb256", ND_PAVGB256 },   
    { "__builtin_ia32_pavgw256", ND_PAVGW256 },   
    { "__builtin_ia32_permvarsi256", ND_PERMVARSI256 },   
    { "__builtin_ia32_vec_ext_v8si", ND_VECEXTV8SI },   
    { "__builtin_ia32_punpckhbw256", ND_PUNPCKHBW256 },
    { "__builtin_ia32_punpckhwd256", ND_PUNPCKHWD256 },
    { "__builtin_ia32_punpckhdq256", ND_PUNPCKHDQ256 },
    { "__builtin_ia32_punpckhqdq256", ND_PUNPCKHQDQ256 },
    { "__builtin_ia32_punpcklbw256", ND_PUNPCKLBW256 },
    { "__builtin_ia32_punpcklwd256", ND_PUNPCKLWD256 },
    { "__builtin_ia32_punpckldq256", ND_PUNPCKLDQ256 },
    { "__builtin_ia32_punpcklqdq256", ND_PUNPCKLQDQ256 },
    { "__builtin_ia32_psadbw256", ND_PSADBW256 },
    { "__builtin_ia32_packsswb256", ND_PACKSSWB256 },
    { "__builtin_ia32_packssdw256", ND_PACKSSDW256 },
    { "__builtin_ia32_packuswb256", ND_PACKUSWB256 },
    { "__builtin_ia32_packusdw256", ND_PACKUSDW256 },
    { "__builtin_ia32_pmulhw256", ND_PMULHW256 },
    { "__builtin_ia32_psadbw128", ND_PSADBW128 }, 
    { "__builtin_ia32_movnti", ND_MOVNTI },   
    { "__builtin_ia32_movnti64", ND_MOVNTI64 },   
    { "__builtin_ia32_movntdq", ND_MOVNTDQ },   
    { "__builtin_ia32_movntpd", ND_MOVNTPD },  
    { "__builtin_parity", ND_PARITY }, 
    { "__builtin_parityl", ND_PARITYL }, 
    { "__builtin_parityll", ND_PARITYLL }, 
    { "__builtin_ia32_mwait", ND_MWAIT }, 
    { "__builtin_ia32_monitor", ND_MONITOR }, 
    { "__builtin_ia32_addsubps", ND_ADDSUBPS }, 
    { "__builtin_ia32_haddps", ND_HADDPS }, 
    { "__builtin_ia32_hsubps", ND_HSUBPS }, 
    { "__builtin_ia32_movshdup", ND_MOVSHDUP }, 
    { "__builtin_ia32_movsldup", ND_MOVSLDUP },
    { "__builtin_ia32_addsubpd", ND_ADDSUBPD }, 
    { "__builtin_ia32_haddpd", ND_HADDPD }, 
    { "__builtin_ia32_hsubpd", ND_HSUBPD },
    { "__builtin_ia32_lddqu", ND_LDDQU },    
    { "__builtin_ia32_phaddw128", ND_PHADDW128 },
    { "__builtin_ia32_phaddd128", ND_PHADDD128 },
    { "__builtin_ia32_phaddsw128", ND_PHADDSW128 },
    { "__builtin_ia32_phaddw", ND_PHADDW },
    { "__builtin_ia32_phaddd", ND_PHADDD },
    { "__builtin_ia32_phaddsw", ND_PHADDSW },    
    { "__builtin_ia32_phsubw128", ND_PHSUBW128 },    
    { "__builtin_ia32_phsubd128", ND_PHSUBD128 },    
    { "__builtin_ia32_phsubsw128", ND_PHSUBSW128 },    
    { "__builtin_ia32_phsubw", ND_PHSUBW },    
    { "__builtin_ia32_phsubd", ND_PHSUBD },    
    { "__builtin_ia32_phsubsw", ND_PHSUBSW },  
    { "__builtin_ia32_pmaddubsw128", ND_PMADDUBSW128 }, 
    { "__builtin_ia32_pmaddubsw", ND_PMADDUBSW }, 
    { "__builtin_ia32_pmulhrsw128", ND_PMULHRSW128 }, 
    { "__builtin_ia32_pmulhrsw", ND_PMULHRSW },
    { "__builtin_ia32_pshufb128", ND_PSHUFB128 },
    { "__builtin_ia32_pshufb", ND_PSHUFB  },
    { "__builtin_ia32_psignb128", ND_PSIGNB128 },
    { "__builtin_ia32_psignw128", ND_PSIGNW128 },
    { "__builtin_ia32_psignd128", ND_PSIGND128 },
    { "__builtin_ia32_psignb", ND_PSIGNB },
    { "__builtin_ia32_psignw", ND_PSIGNW },
    { "__builtin_ia32_psignd", ND_PSIGND },
    { "__builtin_ia32_pabsb128", ND_PABSB128 },
    { "__builtin_ia32_pabsw128", ND_PABSW128 },
    { "__builtin_ia32_pabsd128", ND_PABSD128 },
    { "__builtin_ia32_pabsb", ND_PABSB },
    { "__builtin_ia32_pabsw", ND_PABSW },
    { "__builtin_ia32_pabsd", ND_PABSD },
    { "__builtin_ia32_ptestz128", ND_PTESTZ128 },
    { "__builtin_ia32_ptestc128", ND_PTESTC128 },
    { "__builtin_ia32_ptestnzc128", ND_PTESTNZC128 },
    { "__builtin_ia32_pblendvb128", ND_PBLENDVB128 },
    { "__builtin_ia32_pblendw128", ND_PBLENDW128 },
    { "__builtin_ia32_blendvps", ND_BLENDVPS },
    { "__builtin_ia32_blendvpd", ND_BLENDVPD },
    { "__builtin_ia32_blendps", ND_BLENDPS },
    { "__builtin_ia32_blendpd", ND_BLENDPD },
    { "__builtin_ia32_blendps256", ND_BLENDPS256 },
    { "__builtin_ia32_blendpd256", ND_BLENDPD256 },
    { "__builtin_ia32_dpps", ND_DPPS },
    { "__builtin_ia32_dppd", ND_DPPD },
    { "__builtin_ia32_insertps128", ND_INSERTPS128 },
    { "__builtin_ia32_mpsadbw128", ND_MPSADBW128 },
    { "__builtin_ia32_mpsadbw256", ND_MPSADBW256 },
    { "__builtin_ia32_pminsb128", ND_PMINSB128 },
    { "__builtin_ia32_pmaxsb128", ND_PMAXSB128 },
    { "__builtin_ia32_pminuw128", ND_PMINUW128 },
    { "__builtin_ia32_pmaxuw128", ND_PMAXUW128 },
    { "__builtin_ia32_pminsd128", ND_PMINSD128 },
    { "__builtin_ia32_pmaxsd128", ND_PMAXSD128 },
    { "__builtin_ia32_pminud128", ND_PMINUD128 },
    { "__builtin_ia32_pmaxud128", ND_PMAXUD128 },
    { "__builtin_ia32_pmuldq128", ND_PMULDQ128 },
    { "__builtin_ia32_phminposuw128", ND_PHMINPOSUW128 },
    { "__builtin_ia32_pmovsxbd128", ND_PMOVSXBD128 },
    { "__builtin_ia32_pmovsxwd128", ND_PMOVSXWD128 },
    { "__builtin_ia32_pmovsxbq128", ND_PMOVSXBQ128 },
    { "__builtin_ia32_pmovsxdq128", ND_PMOVSXDQ128 },
    { "__builtin_ia32_pmovsxwq128", ND_PMOVSXWQ128 },
    { "__builtin_ia32_pmovsxbw128", ND_PMOVSXBW128 },
    { "__builtin_ia32_pmovzxbd128", ND_PMOVZXBD128 },
    { "__builtin_ia32_pmovzxwd128", ND_PMOVZXWD128 },
    { "__builtin_ia32_pmovzxbq128", ND_PMOVZXBQ128 },
    { "__builtin_ia32_pmovzxdq128", ND_PMOVZXDQ128 },
    { "__builtin_ia32_pmovzxwq128", ND_PMOVZXWQ128 },
    { "__builtin_ia32_pmovzxbw128", ND_PMOVZXBW128 },    
    { "__builtin_ia32_packusdw128", ND_PACKUSDW128 },  
    { "__builtin_ia32_movntdqa", ND_MOVNTDQA },    
    { "__builtin_ia32_crc32qi", ND_CRC32QI },    
    { "__builtin_ia32_crc32hi", ND_CRC32HI },    
    { "__builtin_ia32_crc32si", ND_CRC32SI },    
    { "__builtin_ia32_crc32di", ND_CRC32DI },
    { "__builtin_ia32_pshufd", ND_PSHUFD },
    { "__builtin_ia32_pshufhw", ND_PSHUFHW },
    { "__builtin_ia32_pshuflw", ND_PSHUFLW },
    { "__builtin_ia32_pshufw", ND_PSHUFW },
    { "__builtin_prefetch", ND_PREFETCH },
    { "__builtin_ia32_rdtsc", ND_RDTSC },
    { "__builtin_ia32_readeflags_u64", ND_READEFLAGS_U64 },
    { "__builtin_ia32_rdsspq", ND_RDSSPQ },   
    { "__builtin_ia32_saveprevssp", ND_SAVEPREVSSP },
    { "__builtin_ia32_setssbsy", ND_SETSSBSY },
    { "__builtin_ia32_slwpcb", ND_SLWPCB },
    { "__builtin_ia32_rdpkru", ND_RDPKRU },
    { "__builtin_ia32_xbegin", ND_XBEGIN },
    { "__builtin_ia32_xend", ND_XEND },    
    { "__builtin_ia32_serialize", ND_SERIALIZE },    
    { "__builtin_ia32_xsusldtrk", ND_XSUSLDTRK },
    { "__builtin_ia32_xresldtrk", ND_XRESLDTRK },
    { "__builtin_ia32_clui", ND_CLUI },
    { "__builtin_ia32_stui", ND_STUI },
    { "__builtin_ia32_testui", ND_TESTUI },
    { "__builtin_ia32_wbnoinvd", ND_WBNOINVD },
    { "__builtin_ia32_xtest", ND_XTEST },
    { "__builtin_ia32_wbinvd", ND_WBINVD },
    { "__builtin_ia32_rdpid", ND_RDPID },
    { "__builtin_ia32_rdfsbase32", ND_RDFSBASE32 },
    { "__builtin_ia32_rdfsbase64", ND_RDFSBASE64 },
    { "__builtin_ia32_rdgsbase32", ND_RDGSBASE32 },
    { "__builtin_ia32_rdgsbase64", ND_RDGSBASE64 },
    { "__builtin_ia32_vzeroall", ND_VZEROALL },
    { "__builtin_ia32_vzeroupper", ND_VZEROUPPER },
    { "__builtin_ia32_femms", ND_FEMMS },
    { "__builtin_ia32_bsrsi", ND_BSRSI },
    { "__builtin_ia32_rdpmc", ND_RDPMC },
    { "__builtin_ia32_rdtscp", ND_RDTSCP },
    { "__builtin_ia32_rolqi", ND_ROLQI },
    { "__builtin_ia32_rolhi", ND_ROLHI },
    { "__builtin_ia32_rorqi", ND_RORQI },
    { "__builtin_ia32_rorhi", ND_RORHI },
    { "__builtin_ia32_bsrdi", ND_BSRDI },    
    { "__builtin_ia32_writeeflags_u64", ND_WRITEEFLAGS_U64 },
    { "__builtin_ia32_incsspq", ND_INCSSPQ },
    { "__builtin_ia32_rstorssp", ND_RSTORSSP },
    { "__builtin_ia32_wrssd", ND_WRSSD },
    { "__builtin_ia32_wrssq", ND_WRSSQ },
    { "__builtin_ia32_wrussd", ND_WRUSSD },
    { "__builtin_ia32_wrussq", ND_WRUSSQ },
    { "__builtin_ia32_clrssbsy", ND_CLRSSBSY },
    { "__builtin_ia32_sbb_u32", ND_SBB_U32 },
    { "__builtin_ia32_addcarryx_u32", ND_ADDCARRYX_U32 },
    { "__builtin_ia32_sbb_u64", ND_SBB_U64 },
    { "__builtin_ia32_addcarryx_u64", ND_ADDCARRYX_U64 },    
    { "__builtin_ia32_tzcnt_u16", ND_TZCNT_U16 },
    { "__builtin_ia32_bextr_u32", ND_BEXTR_U32 },
    { "__builtin_ia32_psubusb256", ND_PSUBUSB256 },
    { "__builtin_ia32_pcmpgtb256_mask", ND_PCMPGTB256_MASK },
    { "__builtin_ia32_pshufb256", ND_PSHUFB256 },
    { "__builtin_ia32_pblendvb256", ND_PBLENDVB256 },
    { "__builtin_ia32_psrldqi128", ND_PSRLDQI128 },
    { "__builtin_ia32_pslldqi128", ND_PSLLDQI128 },
    { "__builtin_ia32_psrldqi256", ND_PSRLDQI256 },
    { "__builtin_ia32_pslldqi256", ND_PSLLDQI256 },
    { "__builtin_ia32_vinsertf128_si256", ND_VINSERTF128_SI256 },        
    { "__builtin_ia32_si256_si", ND_SI256_SI },
    { "__builtin_ia32_si_si256", ND_SI_SI256 },
    { "__builtin_ia32_palignr256", ND_PALIGNR256 },
    { "__builtin_ia32_palignr128", ND_PALIGNR128 },
    { "__builtin_ia32_palignr", ND_PALIGNR },
    { "__builtin_ia32_permti256", ND_VPERM2I128_SI256 },
    { "__builtin_ia32_pblendd256", ND_PBLENDD256 },
    { "__builtin_ia32_vextractf128_si256", ND_VEXTRACTF128_SI256 },
    { "__builtin_ia32_vec_ext_v16qi", ND_VECEXTV16QI },
    { "__builtin_ia32_vec_ext_v8hi", ND_VECEXTV8HI },
    { "__builtin_ia32_andnotsi256", ND_ANDNOTSI256 },
    { "__builtin_ia32_vec_ext_v2di", ND_VECEXTV2DI },
    { "__builtin_ia32_pmulhuw256", ND_PMULHUW256 },
    { "__builtin_ia32_pd_pd256", ND_PD256_PD },
    { "__builtin_ia32_ps_ps256", ND_PS256_PS },
    { "__builtin_ia32_psrlqi256", ND_PSRLQI256 },
    { "__builtin_ia32_psllqi256", ND_PSLLQI256 },
    { "__builtin_ia32_psllwi256", ND_PSLLWI256 },
    { "__builtin_ia32_permdi256", ND_PERMDI256 },
    { "__builtin_ia32_pslldi256", ND_PSLLDI256 }, 
    { "__builtin_ia32_psrldi256", ND_PSRLDI256 },
    { "__builtin_ia32_psradi256", ND_PSRADI256 },
    { "__builtin_ia32_vec_ext_v4hi", ND_VECEXTV4HI },
    { "__builtin_ia32_vec_set_v4hi", ND_VECSETV4HI },
    { "__builtin_ia32_vec_set_v8hi", ND_VECSETV8HI },
    { "__builtin_ia32_vec_set_v16qi", ND_VECSETV16QI },
    { "__builtin_ia32_vec_set_v4si", ND_VECSETV4SI },
    { "__builtin_ia32_vec_set_v2di", ND_VECSETV2DI },
    { "__builtin_ia32_pcmpistrm128", ND_PCMPISTRM128 },
    { "__builtin_ia32_pcmpistri128", ND_PCMPISTRI128 },
    { "__builtin_ia32_pcmpistria128", ND_PCMPISTRIA128 },
    { "__builtin_ia32_pcmpistric128", ND_PCMPISTRIC128 },
    { "__builtin_ia32_pcmpistrio128", ND_PCMPISTRIO128 },
    { "__builtin_ia32_pcmpistris128", ND_PCMPISTRIS128 },
    { "__builtin_ia32_pcmpistriz128", ND_PCMPISTRIZ128 },
    { "__builtin_ia32_pcmpestrm128", ND_PCMPESTRM128 },
    { "__builtin_ia32_pcmpestri128", ND_PCMPESTRI128 },
    { "__builtin_ia32_pcmpestria128", ND_PCMPESTRIA128 },
    { "__builtin_ia32_pcmpestric128", ND_PCMPESTRIC128 },
    { "__builtin_ia32_pcmpestrio128", ND_PCMPESTRIO128 },
    { "__builtin_ia32_pcmpestris128", ND_PCMPESTRIS128 },
    { "__builtin_ia32_pcmpestriz128", ND_PCMPESTRIZ128 },
    { "__builtin_ia32_pclmulqdq128", ND_PCLMULQDQ128 },
    { "__builtin_ia32_dpps256", ND_DPPS256 },
    { "__builtin_ia32_shufpd256", ND_SHUFPD256 },
    { "__builtin_ia32_shufps256", ND_SHUFPS256 },
    { "__builtin_ia32_cmppd", ND_CMPPD },
    { "__builtin_ia32_cmpps", ND_CMPPS },
    { "__builtin_ia32_cmppd256", ND_CMPPD256 },
    { "__builtin_ia32_cmpps256", ND_CMPPS256 },
    { "__builtin_ia32_cmpsd", ND_CMPSD },
    { "__builtin_ia32_cmpss", ND_CMPSS },
    { "__builtin_ia32_vextractf128_pd256", ND_VEXTRACTF128_PD256 },
    { "__builtin_ia32_vextractf128_ps256", ND_VEXTRACTF128_PS256 },
    { "__builtin_ia32_vinsertf128_pd256", ND_VINSERTF128_PD256 },
    { "__builtin_ia32_vinsertf128_ps256", ND_VINSERTF128_PS256 },
    { "__builtin_ia32_vperm2f128_pd256", ND_VPERM2F128_PD256 },
    { "__builtin_ia32_vperm2f128_ps256", ND_VPERM2F128_PS256 },
    { "__builtin_ia32_vperm2f128_si256", ND_VPERM2F128_SI256 },
    { "__builtin_ia32_vpermilpd", ND_VPERMILPD },
    { "__builtin_ia32_vpermilps", ND_VPERMILPS },
    { "__builtin_ia32_vpermilpd256", ND_VPERMILPD256 },
    { "__builtin_ia32_vpermilps256", ND_VPERMILPS256 },
    { "__builtin_ia32_exp2pd_mask", ND_EXP2PD_MASK },
    { "__builtin_ia32_exp2ps_mask", ND_EXP2PS_MASK },
    { "__builtin_ia32_rcp28pd_mask", ND_RCP28PD_MASK },
    { "__builtin_ia32_rcp28ps_mask", ND_RCP28PS_MASK },
    { "__builtin_ia32_rcp28sd_round", ND_RCP28SD_ROUND },
    { "__builtin_ia32_rcp28ss_round", ND_RCP28SS_ROUND },
    { "__builtin_ia32_rsqrt28pd_mask", ND_RSQRT28PD_MASK },
    { "__builtin_ia32_rsqrt28ps_mask", ND_RSQRT28PS_MASK },
    { "__builtin_ia32_rsqrt28sd_round", ND_RSQRT28SD_ROUND },
    { "__builtin_ia32_rsqrt28ss_round", ND_RSQRT28SS_ROUND },
    { "__builtin_ia32_vpshrd_v32hi", ND_VPSHRD_V32HI },
    { "__builtin_ia32_vpshrd_v16si", ND_VPSHRD_V16SI },
    { "__builtin_ia32_vpshrd_v8di", ND_VPSHRD_V8DI },
    { "__builtin_ia32_vpshrd_v16si_mask", ND_VPSHRD_V16SI_MASK },
    { "__builtin_ia32_vpshrd_v8di_mask", ND_VPSHRD_V8DI_MASK },
    { "__builtin_ia32_vpshld_v32hi", ND_VPSHLD_V32HI },
    { "__builtin_ia32_vpshld_v16si", ND_VPSHLD_V16SI },
    { "__builtin_ia32_vpshld_v8di", ND_VPSHLD_V8DI },
    { "__builtin_ia32_vpshld_v16si_mask", ND_VPSHLD_V16SI_MASK },
    { "__builtin_ia32_vpshld_v8di_mask", ND_VPSHLD_V8DI_MASK },
    { "__builtin_ia32_bextri_u32", ND_BEXTR_U32 },
    { "__builtin_ia32_bextri_u64", ND_BEXTR_U64 },
    { "__builtin_ia32_xabort", ND_XABORT },
    { "__builtin_ia32_vpclmulqdq_v4di", ND_VPCLMULQDQ_V4DI },
    { "__builtin_ia32_vpclmulqdq_v8di", ND_VPCLMULQDQ_V8DI },
    { "__builtin_ia32_gatherpfdpd", ND_GATHERPFDPD },
    { "__builtin_ia32_gatherpfdps", ND_GATHERPFDPS },
    { "__builtin_ia32_gatherpfqpd", ND_GATHERPFQPD },
    { "__builtin_ia32_gatherpfqps", ND_GATHERPFQPS },
    { "__builtin_ia32_scatterpfdpd", ND_SCATTERPFDPD },
    { "__builtin_ia32_scatterpfdps", ND_SCATTERPFDPS },
    { "__builtin_ia32_scatterpfqpd", ND_SCATTERPFQPD },
    { "__builtin_ia32_scatterpfqps", ND_SCATTERPFQPS },
};


char *prefix_builtin(const char *name) {
    const char *prefix = "__builtin_";
    size_t len = strlen(prefix) + strlen(name) + 1;
    char *buf = malloc(len);
    if (!buf) return NULL; 
    strcpy(buf, prefix);
    strcat(buf, name);
    return buf;
}


int builtin_enum(Token *tok) {
    for (size_t i = 0; i < sizeof(builtin_table) / sizeof(builtin_table[0]); i++) {
        if (equal(tok, builtin_table[i].name))
            return builtin_table[i].node_kind;
    }
    return -1; // not found
}


void gen_builtin_alloca(Node *node)
{
  int align = node->val > 16 ? node->val : 16;
  Obj *fn = get_current_fn();
  if (fn->stack_align > 16)
    align = MAX(align, fn->stack_align);

  if (!fn->alloca_bottom) {
    println("  mov %%rsp, %%rax");
    println("  sub %%rdi, %%rax");
    println("  and $-%d, %%rax", align);
    println("  mov %%rax, %%rsp");
    return;
  }

  int off = fn->alloca_bottom->offset;
  const char *ptr = fn->alloca_bottom->ptr;
  if (is_omit_fp(fn)) {
    off += fn->stack_size;
    ptr = "%rsp";
  }

  println("  mov %d(%s), %%rax", off, ptr);
  println("  mov %%rax, %%rcx");
  println("  sub %%rsp, %%rcx");
  println("  mov %%rax, %%rdx");
  println("  sub %%rdi, %%rdx");
  println("  and $-%d, %%rdx", align);
  println("  mov %%rax, %%rsi");
  println("  sub %%rdx, %%rsi");

  println("  mov %%rsp, %%r8");
  println("  sub %%rsi, %%rsp");
  println("  mov %%rsp, %%r9");

  println("1:");
  println("  cmp $0, %%rcx");
  println("  je 2f");
  println("  mov (%%r8), %%r11b");
  println("  mov %%r11b, (%%r9)");
  println("  inc %%r8");
  println("  inc %%r9");
  println("  dec %%rcx");
  println("  jmp 1b");
  println("2:");

  println("  mov %%rdx, %d(%s)", off, ptr);
  println("  mov %%rdx, %%rax");
}

void gen_memset(Node *node) {
  if (opt_fbuiltin) {
    gen_expr(node->builtin_dest);
    push_tmp();
    gen_expr(node->builtin_val);
    push_tmp();
    gen_expr(node->builtin_size);
    push_tmp();
    pop_tmp("%rcx");
    pop_tmp("%rsi");
    pop_tmp("%rdi");
    println("  mov %%rdi, %%r9");
    println("  mov %%sil, %%al");
    println("  cld");
    println("  rep stosb");
    println("  mov %%r9, %%rax");
  }
}

void gen_memcpy(Node *node) {
  if (opt_fbuiltin) {
    gen_expr(node->builtin_dest);
    push_tmp();
    gen_expr(node->builtin_src);
    push_tmp();
    gen_expr(node->builtin_size);
    println("  mov %%rax, %%rcx");
    pop_tmp("%rsi");
    pop_tmp("%rdi");
    println("  mov %%rdi, %%rax");
    println("  cld");
    println("  rep movsb");
    return;
  }
}

void gen_builtin_single(Node *node, const char *insn, const char *reg) {
    gen_expr(node->builtin_val);
    println("  %s %%%s, %%%s", insn, reg, reg);
}

void gen_builtin_stdc_bit_ceil(Node *node)  {
  int c = count();
  gen_expr(node->lhs);
  int sz = node->lhs->ty->size;

  if (sz == 8) {
    println("  cmp $1, %%rax");
    println("  ja .Lceil_greater_%d", c);
    println("  mov $1, %%rax");
    println("  jmp .Lceil_done_%d", c);
    println(".Lceil_greater_%d:", c);
    println("  dec %%rax");
    println("  bsr %%rax, %%rax");
    println("  add $1, %%rax");
    println("  mov %%rax, %%rcx");
    println("  mov $1, %%rax");
    println("  shl %%cl, %%rax");
    println(".Lceil_done_%d:", c);
  } else {
    println("  cmp $1, %%eax");
    println("  ja .Lceil_greater_%d", c);
    println("  mov $1, %%eax");
    println("  jmp .Lceil_done_%d", c);
    println(".Lceil_greater_%d:", c);
    println("  dec %%eax");
    println("  bsr %%eax, %%eax");
    println("  add $1, %%eax");
    println("  mov %%eax, %%ecx");
    println("  mov $1, %%eax");
    println("  shl %%cl, %%eax");
    println(".Lceil_done_%d:", c);
  }
}

void gen_add_overflow(Node *node) {
  int c = count();
  Type *ty = node->builtin_dest->ty;
  if (ty->base)
    ty = ty->base;

  gen_expr(node->lhs);
  if (ty->size == 16) pushx_tmp(); else push_tmp();
  gen_expr(node->rhs);
  if (ty->size == 16) pushx_tmp(); else push_tmp();
  gen_expr(node->builtin_dest);
  push_tmp();

  pop_tmp("%rdx");
  if (ty->size == 16) popx_tmp("%rcx", "%rsi"); else pop_tmp("%rsi");
  if (ty->size == 16) popx_tmp("%rax", "%rdi"); else pop_tmp("%rdi");

  if (ty->size == 1) {
      println("  mov %%dil, %%al");
      println("  add %%sil, %%al");
      println("  mov %%al, (%%rdx)");
  } else if (ty->size == 2) {
      println("  mov %%di, %%ax");
      println("  add %%si, %%ax");
      println("  mov %%ax, (%%rdx)");
  } else if (ty->size == 4) {
      println("  mov %%edi, %%eax");
      println("  add %%esi, %%eax");
      println("  mov %%eax, (%%rdx)");
  } else if (ty->size == 8) {
      println("  mov %%rdi, %%rax");
      println("  add %%rsi, %%rax");
      println("  mov %%rax, (%%rdx)");
  } else if (ty->size == 16) {
      println("  add %%rcx, %%rax");
      println("  adc %%rsi, %%rdi");
      println("  mov %%rax, (%%rdx)");
      println("  mov %%rdi, 8(%%rdx)");
  }

  if (ty->is_unsigned)
    println("  setc %%al");
  else
    println("  seto %%al");
  println("  movzx %%al, %%eax");

  println("  cmp $0, %%eax");
  println("  jne .Loverflowa%d", c);
  println("  mov $0, %%eax");
  println("  jmp .Lenda%d", c);
  println(".Loverflowa%d:", c);
  println("  mov $1, %%eax");
  println(".Lenda%d:", c);
}

void gen_sub_overflow(Node *node) {
    int c = count();
    Type *ty = node->builtin_dest->ty;
    if (ty->base)
      ty = ty->base;

    gen_expr(node->lhs);
    if (ty->size == 16)
      pushx_tmp();
    else
      push_tmp();
    gen_expr(node->rhs);
    if (ty->size == 16)
      pushx_tmp();
    else
      push_tmp();
    gen_expr(node->builtin_dest);
    push_tmp();

    pop_tmp("%rdx");
    if (ty->size == 16)
      popx_tmp("%rcx", "%rsi");
    else
      pop_tmp("%rsi");
    if (ty->size == 16)
      popx_tmp("%rax", "%rdi");
    else
      pop_tmp("%rdi");

    if (ty->size == 1) {
        if (node->lhs->ty->is_unsigned) {
          println("  movzbl %%dil, %%eax");
        } else {
          println("  movsbl %%dil, %%eax");
        }
        println("  movslq %%eax, %%rax");

        if (node->rhs->ty->is_unsigned) {
          println("  movzbl %%sil, %%ecx");
        } else {
          println("  movsbl %%sil, %%ecx");
        }
        println("  movslq %%ecx, %%rcx");

        println("  sub %%rcx, %%rax");
        println("  mov %%al, (%%rdx)");

        if (ty->is_unsigned) {
          println("  cmp $0, %%rax");
          println("  jl .Loverflows%d", c);
          println("  cmp $255, %%rax");
          println("  jg .Loverflows%d", c);
        } else {
          println("  cmp $-128, %%rax");
          println("  jl .Loverflows%d", c);
          println("  cmp $127, %%rax");
          println("  jg .Loverflows%d", c);
        }
        println("  mov $0, %%eax");
        println("  jmp .Lends%d", c);
        println(".Loverflows%d:", c);
        println("  mov $1, %%eax");
        println(".Lends%d:", c);
        return;
    } else if (ty->size == 2) {
        if (node->lhs->ty->is_unsigned) {
          println("  movzwl %%di, %%eax");
        } else {
          println("  movswl %%di, %%eax");
        }
        println("  movslq %%eax, %%rax");

        if (node->rhs->ty->is_unsigned) {
          println("  movzwl %%si, %%ecx");
        } else {
          println("  movswl %%si, %%ecx");
        }
        println("  movslq %%ecx, %%rcx");

        println("  sub %%rcx, %%rax");
        println("  mov %%ax, (%%rdx)");

        if (ty->is_unsigned) {
          println("  cmp $0, %%rax");
          println("  jl .Loverflows%d", c);
          println("  cmp $65535, %%rax");
          println("  jg .Loverflows%d", c);
        } else {
          println("  cmp $-32768, %%rax");
          println("  jl .Loverflows%d", c);
          println("  cmp $32767, %%rax");
          println("  jg .Loverflows%d", c);
        }
        println("  mov $0, %%eax");
        println("  jmp .Lends%d", c);
        println(".Loverflows%d:", c);
        println("  mov $1, %%eax");
        println(".Lends%d:", c);
        return;
    } else if (ty->size == 4) {
        println("  mov %%edi, %%eax");
        if (!node->lhs->ty->is_unsigned)
          println("  movslq %%eax, %%rax");

        println("  mov %%esi, %%ecx");
        if (!node->rhs->ty->is_unsigned)
          println("  movslq %%ecx, %%rcx");

        println("  sub %%rcx, %%rax");
        println("  mov %%eax, (%%rdx)");

        if (ty->is_unsigned) {
          println("  cmp $0, %%rax");
          println("  jl .Loverflows%d", c);
          println("  mov $4294967295, %%rcx");
          println("  cmp %%rcx, %%rax");
          println("  jg .Loverflows%d", c);
        } else {
          println("  mov $-2147483648, %%rcx");
          println("  cmp %%rcx, %%rax");
          println("  jl .Loverflows%d", c);
          println("  mov $2147483647, %%rcx");
          println("  cmp %%rcx, %%rax");
          println("  jg .Loverflows%d", c);
        }
        println("  mov $0, %%eax");
        println("  jmp .Lends%d", c);
        println(".Loverflows%d:", c);
        println("  mov $1, %%eax");
        println(".Lends%d:", c);
        return;
    } else if (ty->size == 8) {
        println("  mov %%rdi, %%rax");
        if (node->lhs->ty->is_unsigned) {
          println("  xor %%rcx, %%rcx");
        } else {
          println("  mov %%rdi, %%rcx");
          println("  sar $63, %%rcx");
        }

        println("  mov %%rsi, %%rbx");
        if (node->rhs->ty->is_unsigned) {
          println("  xor %%r8, %%r8");
        } else {
          println("  mov %%rsi, %%r8");
          println("  sar $63, %%r8");
        }

        println("  sub %%rbx, %%rax");
        println("  sbb %%r8, %%rcx");

        println("  mov %%rax, (%%rdx)");

        if (ty->is_unsigned) {
          println("  test %%rcx, %%rcx");
          println("  sete %%al");
          println("  xor $1, %%al");
          println("  movzx %%al, %%eax");
        } else {
          println("  mov %%rax, %%r8");
          println("  sar $63, %%r8");
          println("  cmp %%r8, %%rcx");
          println("  sete %%al");
          println("  xor $1, %%al");
          println("  movzx %%al, %%eax");
        }

        return;
    } else if (ty->size == 16) {
        println("  sub %%rcx, %%rax");
        println("  sbb %%rsi, %%rdi");
        println("  mov %%rax, (%%rdx)");
        println("  mov %%rdi, 8(%%rdx)");
    }

    if (ty->is_unsigned)
      println("  setc %%al");
    else
      println("  seto %%al");
    println("  movzx %%al, %%eax");
    println("  cmp $0, %%eax");
    println("  jne .Loverflows%d", c);
    println("  mov $0, %%eax");
    println("  jmp .Lends%d", c);
    println(".Loverflows%d:", c);
    println("  mov $1, %%eax");
    println(".Lends%d:", c);
}

void gen_mul_overflow(Node *node) {
  int c = count();
  Type *ty = node->lhs->ty;
  if (ty->base)
    ty = ty->base;
  int size = ty->size;
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  push_tmp();
  gen_expr(node->builtin_dest);
  push_tmp();
  pop_tmp("%rcx");
  pop_tmp("%rsi");
  pop_tmp("%rdi");
  if (size == 1) {
    println("  mov %%dil, %%al");
    if (ty->is_unsigned)
      println("  mul %%sil");
    else
      println("  imul %%sil");
    println("  jo .L.overflowm%d", c);
    println("  mov %%al, (%%rcx)");
    println("  mov $0, %%eax");
    println("  jmp .L.donem%d", c);
  } else if (size == 2) {
    println("  mov %%di, %%ax");
    if (ty->is_unsigned)
      println("  mul %%si");
    else
      println("  imul %%si");
    println("  jo .L.overflowm%d", c);
    println("  mov %%ax, (%%rcx)");
    println("  mov $0, %%eax");
    println("  jmp .L.donem%d", c);
  } else if (size == 4) {
    println("  mov %%edi, %%eax");
    if (ty->is_unsigned)
      println("  mul %%esi");
    else
      println("  imul %%esi");
    println("  jo .L.overflowm%d", c);
    println("  mov %%eax, (%%rcx)");
    println("  mov $0, %%eax");
    println("  jmp .L.donem%d", c);
  } else if (size == 8) {
    println("  mov %%rdi, %%rax");
    if (ty->is_unsigned)
      println("  mul %%rsi");
    else
      println("  imul %%rsi");
    println("  jo .L.overflowm%d", c);
    println("  mov %%rax, (%%rcx)");
    println("  mov $0, %%rax");
    println("  jmp .L.donem%d", c);
  }
  println(".L.overflowm%d:", c);
  if (size == 1) println("  mov %%al, (%%rcx)");
  else if (size == 2) println("  mov %%ax, (%%rcx)");
  else if (size == 4) println("  mov %%eax, (%%rcx)");
  else if (size == 8) println("  mov %%rax, (%%rcx)");

  println("  mov $1, %%rax");
  println(".L.donem%d:", c);
}

void gen_umul_overflow(Node *node) {
    int c = count();
    Type *ty = node->lhs->ty;
    if (ty->base)
        ty = ty->base;
    int size = ty->size;

    gen_expr(node->lhs);
    push_tmp();
    gen_expr(node->rhs);
    push_tmp();
    gen_expr(node->builtin_dest);
    push_tmp();

    pop_tmp("%rdx");
    pop_tmp("%rsi");
    pop_tmp("%rdi");
    println("  mov %%rdx, %%rcx");

    if (size == 1) {
        println("  movzbl %%di, %%eax");
        println("  movzbl %%si, %%ebx");
        println("  mul %%bl");
        println("  jc .Loverflowm%d", c);
    } else if (size == 2) {
        println("  movzwl %%di, %%eax");
        println("  movzwl %%si, %%ebx");
        println("  mul %%bx");
        println("  jc .Loverflowm%d", c);
    } else if (size == 4) {
        println("  mov %%edi, %%eax");
        println("  mul %%esi");
        println("  jc .Loverflowm%d", c);
    } else if (size >= 8) {
        println("  mov %%rdi, %%rax");
        println("  mul %%rsi");
        println("  test %%rdx, %%rdx");
        println("  jnz .Loverflowm%d", c);
    }

    println("  test %%rcx, %%rcx");
    println("  jz .Ldonem%d", c);
    if (size == 1) println("  mov %%al, (%%rcx)");
    else if (size == 2) println("  mov %%ax, (%%rcx)");
    else if (size == 4) println("  mov %%eax, (%%rcx)");
    else if (size == 8) println("  mov %%rax, (%%rcx)");

    println(".Ldonem%d:", c);
    println("  mov $0, %%rax");
    println("  jmp .Lend%d", c);

    println(".Loverflowm%d:", c);
    println("  test %%rcx, %%rcx");
    println("  jz .Loverflow_end%d", c);
    if (size == 1) println("  movb $0, (%%rcx)");
    else if (size == 2) println("  movw $0, (%%rcx)");
    else if (size == 4) println("  movl $0, (%%rcx)");
    else if (size == 8) println("  movq $0, (%%rcx)");
    println(".Loverflow_end%d:", c);
    println("  mov $1, %%rax");
    println(".Lend%d:", c);
}

void gen_uadd_overflow(Node *node) {
  int c = count();
  Type *ty = node->builtin_dest->ty;
  if (ty->base)
      ty = ty->base;

  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  push_tmp();
  gen_expr(node->builtin_dest);
  push_tmp();

  pop_tmp("%rdx");
  pop_tmp("%rsi");
  pop_tmp("%rdi");

  if (ty->size == 1) {
      println("  mov %%dil, %%al");
      println("  add %%sil, %%al");
      println("  mov %%al, (%%rdx)");
  } else if (ty->size == 2) {
      println("  mov %%di, %%ax");
      println("  add %%si, %%ax");
      println("  mov %%ax, (%%rdx)");
  } else if (ty->size == 4) {
      println("  mov %%edi, %%eax");
      println("  add %%esi, %%eax");
      println("  mov %%eax, (%%rdx)");
  } else {
      println("  mov %%rdi, %%rax");
      println("  add %%rsi, %%rax");
      println("  mov %%rax, (%%rdx)");
  }
  println("  setc %%al");
  println("  movzx %%al, %%eax");

  println("  cmp $0, %%eax");
  println("  jne .Loverflowa%d", c);
  println("  mov $0, %%eax");
  println("  jmp .Lenda%d", c);
  println(".Loverflowa%d:", c);
  println("  mov $1, %%eax");
  println(".Lenda%d:", c);
}

void gen_alloc(Node *node) {
  gen_expr(node->lhs);
  println("  mov %%rax, %%rdi");
  println("  sub %%rdi, %%rsp");
  println("  mov %%rsp, %%rax");
}

void gen_prefetch(Node *node) {
  Node *ptr = node->builtin_args[0];
  Node *rw = node->builtin_args[1];
  Node *locality = node->builtin_args[2];
  gen_expr(ptr);
  push_tmp();
  if (rw)
    gen_expr(rw);
  if (locality)
    gen_expr(locality);

  int loc = 3;
    if (locality && locality->kind == ND_NUM) {
        loc = locality->val;
    }

    const char *instr;
    switch (loc) {
        case 0: instr = "prefetchnta"; break;
        case 1: instr = "prefetcht2"; break;
        case 2: instr = "prefetcht1"; break;
        case 3: instr = "prefetcht0"; break;
        default: instr = "prefetcht0"; break;
    }

    pop_tmp("%rax");
    println("  %s (%%rax)", instr);
}

void gen_builtin_clz(Node *node) {
    gen_expr(node->builtin_val);
    println("  bsr %%eax, %%eax");
    println("  xor $31, %%eax");
}

void gen_builtin_clzl(Node *node) {
    gen_expr(node->builtin_val);
    println("  bsr %%rax, %%rax");
    println("  xor $63, %%eax");
}

void gen_builtin_bswap16(Node *node) {
    gen_expr(node->builtin_val);
    println("  movzwl %%ax, %%eax");
    println("  rol $8, %%ax");
}

void gen_builtin_bswap32(Node *node) {
    gen_expr(node->builtin_val);
    println("  bswap %%eax");
}

void gen_builtin_bswap64(Node *node) {
    gen_expr(node->builtin_val);
    println("  bswap %%rax");
}
void gen_builtin_ceil(Node *node) {
    gen_expr(node->builtin_val);
    println("  roundsd $2, %%xmm0, %%xmm0");
}

void gen_builtin_floor(Node *node) {
    gen_expr(node->builtin_val);
    println("  roundsd $1, %%xmm0, %%xmm0");
}

void gen_builtin_ceilf(Node *node) {
    gen_expr(node->builtin_val);
    println("  roundss $2, %%xmm0, %%xmm0");
}

void gen_builtin_floorf(Node *node) {
    gen_expr(node->builtin_val);
    println("  roundss $1, %%xmm0, %%xmm0");
}

void gen_builtin_ceill(Node *node) {
    gen_expr(node->builtin_val);
    // push long double arg from st0 if needed, apply ceil via x87
    // set rounding mode to UP (RC=10b, bits 11:10 of CW), call frndint, restore
    println("  subw $2, %%sp");
    println("  fnstcw (%%sp)");
    println("  movw (%%sp), %%ax");
    println("  andw $0xF3FF, %%ax");
    println("  orw  $0x0800, %%ax");  // RC=10b (toward +inf)
    println("  movw %%ax, 2(%%sp)");
    println("  fldcw 2(%%sp)");
    println("  frndint");
    println("  fldcw (%%sp)");
    println("  addw $2, %%sp");
}

void gen_builtin_floorl(Node *node) {
    gen_expr(node->builtin_val);
    println("  subw $2, %%sp");
    println("  fnstcw (%%sp)");
    println("  movw (%%sp), %%ax");
    println("  andw $0xF3FF, %%ax");
    println("  orw  $0x0400, %%ax");  // RC=01b (toward -inf)
    println("  movw %%ax, 2(%%sp)");
    println("  fldcw 2(%%sp)");
    println("  frndint");
    println("  fldcw (%%sp)");
    println("  addw $2, %%sp");
}

void gen_builtin_frame_address(Node *node) {
    int c = count();

    gen_expr(node->lhs);

    if (is_omit_fp(get_current_fn())) {
        // With -fomit-frame-pointer: level 0 returns %rsp,
        // level > 0 returns NULL (can't walk the chain).
        println("  cmp $0, %%rax");
        println("  jne .Lframe_address_null%d", c);
        println("  mov %%rsp, %%rax");
        println("  jmp .Lframe_address_return%d", c);
        println(".Lframe_address_null%d:", c);
        println("  mov $0, %%rax");
        println(".Lframe_address_return%d:", c);
        return;
    }

    println("  mov $64, %%rdi");
    println("  cmp %%rax, %%rdi");
    println("  ja .Lframe_address_ok%d", c);
    println("  jmp .Lframe_address_null%d", c);

    println(".Lframe_address_ok%d:", c);

    println("  cmp $0, %%rax");
    println("  je .Lframe_address_%d", c);
    println("  mov %%rbp, %%rcx");

    println(".Lframe_address_loop%d:", c);
    println("  test %%rax, %%rax");
    println("  jz .Lframe_address_done%d", c);
    println("  test %%rcx, %%rcx");
    println("  jz .Lframe_address_null%d", c);
    println("  mov (%%rcx), %%rcx");
    println("  sub $1, %%rax");
    println("  jmp .Lframe_address_loop%d", c);

    println(".Lframe_address_done%d:", c);
    println("  mov %%rcx, %%rax");
    println("  jmp .Lframe_address_return%d", c);

    println(".Lframe_address_%d:", c);
    println("  mov %%rbp, %%rax");
    println("  jmp .Lframe_address_return%d", c);

    println(".Lframe_address_null%d:", c);
    println("  mov $0, %%rax");

    println(".Lframe_address_return%d:", c);
}

void gen_builtin_expect(Node *node) {
    gen_expr(node->lhs);
    push_tmp();
    gen_expr(node->rhs);
    pop_tmp("%rdi");
    println("  cmp %%rax, %%rdi");
    println("  mov %%rdi, %%rax");
}

void gen_builtin_abort(Node *node) {
    (void)node;
    println("  call abort");
}

void gen_builtin_return_address(Node *node) {
    println("  mov %%rbp, %%rax");
    int tmpdepth = eval(node->lhs);

    for (int i = 0; i < tmpdepth; i++) {
      println("  mov (%%rax), %%rax");
    }

    println("  mov 8(%%rax), %%rax");
}

void gen_builtin_isnan(Node *node) {
    gen_expr(node->builtin_val);
    if (node->builtin_val->ty->kind == TY_FLOAT) {
        println("  movss %%xmm0, %%xmm1");
        println("  ucomiss %%xmm1, %%xmm1");
    } else {
        println("  ucomisd %%xmm0, %%xmm0");
    }

    println("  setp %%al");
    println("  movzx %%al, %%eax");
}

void gen_builtin_nanf(Node *node) {
    union {
      float f;
      uint32_t i;
    } u;
    u.f = node->fval;
    println("  mov $%u, %%eax", u.i);
    println("  movd %%eax, %%xmm0");
}

void gen_builtin_nan(Node *node) {
    union {
      double d;
      uint64_t i;
    } u;
    u.d = node->fval;
    println("  movq $%lu, %%rax", u.i);
    println("  movq %%rax, %%xmm0");
}

void gen_builtin_nanl(Node *node) {
    union {
      long double ld;
      uint8_t bytes[10];
    } u;
    u.ld = node->fval;

    for (int i = 0; i < 10; i++)
      println("  movb $%d, -%d(%%rsp)", u.bytes[i], 10 - i);

    println("  fldt -10(%%rsp)");
}

// ============================================================
// Phase 1: Misc instruction emitters, Atomic ops, CRC32
// (no static helper dependencies)
// ============================================================

void gen_tzcnt_u16(Node *node) {
  gen_expr(node->lhs);
  println("  testw %%ax, %%ax");
  println("  jne 1f");
  println("  movl $16, %%eax");
  println("  jmp 2f");
  println("1:");
  println("  bsfw %%ax, %%ax");
  println("2:");
}

void gen_bextr_u32(Node *node) {
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  println("  movl %%eax, %%ecx");
  pop_tmp("%rax");

  println("  movl %%ecx, %%edx");
  println("  shrl $8, %%edx");
  println("  andl $0xff, %%edx");
  println("  andl $0xff, %%ecx");

  println("  testl %%edx, %%edx");
  println("  je 1f");

  println("  cmpl $32, %%ecx");
  println("  jae 1f");

  println("  movl $32, %%esi");
  println("  subl %%ecx, %%esi");
  println("  cmpl %%esi, %%edx");
  println("  cmova %%esi, %%edx");

  println("  shrl %%cl, %%eax");

  println("  movl %%edx, %%ecx");
  println("  cmpl $32, %%ecx");
  println("  jae 3f");
  println("  movl $1, %%esi");
  println("  shll %%cl, %%esi");
  println("  decl %%esi");
  println("  andl %%esi, %%eax");
  println("  jmp 2f");
  println("3:");
  println("  jmp 2f");

  println("1:");
  println("  xorl %%eax, %%eax");
  println("2:");
}

void gen_bextr_u64(Node *node) {
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  println("  movl %%eax, %%ecx");
  pop_tmp("%rax");

  println("  movl %%ecx, %%edx");
  println("  shrl $8, %%edx");
  println("  andl $0xff, %%edx");
  println("  andl $0xff, %%ecx");

  println("  testl %%edx, %%edx");
  println("  je 1f");

  println("  cmpq $64, %%rcx");
  println("  jae 1f");

  println("  movq $64, %%rsi");
  println("  subq %%rcx, %%rsi");
  println("  cmpq %%rsi, %%rdx");
  println("  cmova %%rsi, %%rdx");

  println("  shrq %%cl, %%rax");

  println("  movq %%rdx, %%rcx");
  println("  cmpq $64, %%rcx");
  println("  jae 3f");
  println("  movq $1, %%rsi");
  println("  shlq %%cl, %%rsi");
  println("  decq %%rsi");
  println("  andq %%rsi, %%rax");
  println("  jmp 2f");
  println("3:");
  println("  jmp 2f");

  println("1:");
  println("  xorl %%eax, %%eax");
  println("2:");
}

void gen_binop1(Node *node, const char *insn) {
  println("  %s %%rax", insn);
}

void gen_binop2(Node *node, const char *insn) {
  println("  %s %s", insn, reg_ax(node->ty->size));
}

void gen_nothing(Node *node) {
  println("  mov $0, %%rax");
}

void gen_singleop(Node *node, const char *insn) {
  println("  %s", insn);
}

void gen_fetchadd(Node *node) {
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  if (node->ty->size == 16) {
    println("  mov %%rax, %%r9"); // val low
    println("  mov %%rdx, %%r11"); // val high
    pop_tmp("%rdi"); // addr

    println("  mov (%%rdi), %%rax"); // old low
    println("  mov 8(%%rdi), %%rdx"); // old high

    println("1:");
    println("  mov %%rax, %%rbx");
    println("  add %%r9, %%rbx");
    println("  mov %%rdx, %%rcx");
    println("  adc %%r11, %%rcx");

    println("  lock cmpxchg16b (%%rdi)");
    println("  jnz 1b");
    return;
  }
  pop_tmp("%rdi");
  println("  lock xadd %s, (%%rdi)", reg_ax(node->ty->size));
  if (node->ty->size == 1)
    println("  movzbl %%al, %%eax");
  else if (node->ty->size == 2)
    println("  movzwl %%ax, %%eax");
}

void gen_add_fetch(Node *node) {
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  if (node->ty->size == 16) {
    println("  mov %%rax, %%r9"); // val low
    println("  mov %%rdx, %%r11"); // val high
    pop_tmp("%rdi"); // addr

    println("  mov (%%rdi), %%rax"); // old low
    println("  mov 8(%%rdi), %%rdx"); // old high

    println("1:");
    println("  mov %%rax, %%rbx");
    println("  add %%r9, %%rbx");
    println("  mov %%rdx, %%rcx");
    println("  adc %%r11, %%rcx");

    println("  lock cmpxchg16b (%%rdi)");
    println("  jnz 1b");

    println("  mov %%rbx, %%rax");
    println("  mov %%rcx, %%rdx");
    return;
  }
  pop_tmp("%rdi");
  println("  mov %%rax, %%rdx");
  println("  lock xadd %s, (%%rdi)", reg_ax(node->ty->size));
  println("  add %s, %s", reg_ax(node->ty->size), reg_dx(node->ty->size));
  println("  mov %%rdx, %%rax");
  if (node->ty->size == 1)
    println("  movzbl %%al, %%eax");
  else if (node->ty->size == 2)
    println("  movzwl %%ax, %%eax");
}

void gen_sub_fetch(Node *node) {
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  if (node->ty->size == 16) {
    println("  mov %%rax, %%r9"); // val low
    println("  mov %%rdx, %%r11"); // val high
    pop_tmp("%rdi"); // addr

    println("  mov (%%rdi), %%rax"); // old low
    println("  mov 8(%%rdi), %%rdx"); // old high

    println("1:");
    println("  mov %%rax, %%rbx");
    println("  sub %%r9, %%rbx");
    println("  mov %%rdx, %%rcx");
    println("  sbb %%r11, %%rcx");

    println("  lock cmpxchg16b (%%rdi)");
    println("  jnz 1b");

    println("  mov %%rbx, %%rax");
    println("  mov %%rcx, %%rdx");
    return;
  }
  println("  mov %%rax, %%rdx");
  pop_tmp("%rdi");
  println("  neg %s", reg_ax(node->ty->size));
  println("  lock xadd %s, (%%rdi)", reg_ax(node->ty->size));
  println("  sub %s, %s", reg_dx(node->ty->size), reg_ax(node->ty->size));
  if (node->ty->size == 1)
    println("  movzbl %%al, %%eax");
  else if (node->ty->size == 2)
    println("  movzwl %%ax, %%eax");
}

void gen_fetchsub(Node *node) {
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  if (node->ty->size == 16) {
    println("  mov %%rax, %%r9"); // val low
    println("  mov %%rdx, %%r11"); // val high
    pop_tmp("%rdi"); // addr

    println("  mov (%%rdi), %%rax"); // old low
    println("  mov 8(%%rdi), %%rdx"); // old high

    println("1:");
    println("  mov %%rax, %%rbx");
    println("  sub %%r9, %%rbx");
    println("  mov %%rdx, %%rcx");
    println("  sbb %%r11, %%rcx");

    println("  lock cmpxchg16b (%%rdi)");
    println("  jnz 1b");
    return;
  }
  pop_tmp("%rdi");
  println("  neg %s", reg_ax(node->ty->size));
  println("  lock xadd %s, (%%rdi)", reg_ax(node->ty->size));
  if (node->ty->size == 1)
    println("  movzbl %%al, %%eax");
  else if (node->ty->size == 2)
    println("  movzwl %%ax, %%eax");
}

void gen_crc32qi(Node *node) {
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  pop_tmp("%rcx");
  println("  crc32b %%al, %%ecx");
  println("  movl %%ecx, %%eax");
}

void gen_crc32di(Node *node) {
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  pop_tmp("%rcx");
  println("  crc32q %%rax, %%rcx");
  println("  movl %%ecx, %%eax");
}

void gen_crc32hi(Node *node) {
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  pop_tmp("%rcx");
  println("  crc32w %%ax, %%ecx");
  println("  movl %%ecx, %%eax");
}

void gen_crc32si(Node *node) {
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  pop_tmp("%rcx");
  println("  crc32l %%eax, %%ecx");
  println("  movl %%ecx, %%eax");
}

// ============================================================
// Phase 2: Platform Intrinsics (Group A) and CAS/Atomic (Group H)
// Dependencies: gen_addr, load (now non-static)
// ============================================================

void gen_release(Node *node) {
  gen_expr(node->lhs);
  println("  mov %%rax, %%rdi");
  
  if (node->ty->size == 16) {
      println("  xor %%rax, %%rax");
      println("  mov %%rax, (%%rdi)");
      println("  mov %%rax, 8(%%rdi)");
      return;
  }

  println("  xor %%eax, %%eax");
  println("  mov %s, (%%rdi)", reg_ax(node->ty->size));
}

void gen_rdtsc(Node *node) {
  println("  rdtsc");
  println("  shl $32, %%rdx");
  println("  or %%rdx, %%rax");
}

void gen_rdpkru(Node *node) {
  println("  movl $0, %%eax");
  println("  movl %%eax, %%ecx");
  println("  rdpkru");
}

void gen_bsrsi(Node *node) {
  gen_expr(node->lhs);
  println("  bsrl %%eax, %%eax");
}

void gen_bsrdi(Node *node) {
  gen_expr(node->lhs);
  println("  bsrq %%rax, %%rax");
}

void gen_rdpmc(Node *node) {
  gen_expr(node->lhs);
  println("  mov %%eax, %%ecx"); 
  println("  rdpmc");
}

void gen_rdtscp(Node *node) {
  gen_expr(node->lhs);
  println("  movq %%rax, %%rdi");
  println("  rdtscp");        
  println("  movl %%ecx, (%%rdi)"); 
  println("  movl %%edx, %%edx");  
  println("  salq $32, %%rdx");      
  println("  or %%rdx, %%rax");     
}

void gen_rolqi(Node *node) {
  gen_expr(node->lhs);
  println("  mov %%al, %%bl"); 
  gen_expr(node->rhs); 
  println("  mov %%al, %%cl");  
  println("  rolb %%cl, %%bl"); 
  println("  movzb %%bl, %%rax"); 
}

void gen_rorqi(Node *node) {
  gen_expr(node->lhs);
  println("  mov %%al, %%bl"); 
  gen_expr(node->rhs); 
  println("  mov %%al, %%cl");  
  println("  rorb %%cl, %%bl"); 
  println("  movzb %%bl, %%rax"); 
}

void gen_rolhi(Node *node) {
  gen_expr(node->lhs);
  println("  mov %%ax, %%bx");  
  gen_expr(node->rhs);  
  println("  mov %%al, %%cl"); 
  println("  rolw %%cl, %%bx");
  println("  movzx %%bx, %%rax");  
}

void gen_rorhi(Node *node) {
  gen_expr(node->lhs);
  println("  mov %%ax, %%bx");  
  gen_expr(node->rhs);  
  println("  mov %%al, %%cl"); 
  println("  rorw %%cl, %%bx");
  println("  movzx %%bx, %%rax");  
}

void gen_readeflags_u64(Node *node) {
  println("  pushfq");
  println("  popq %%rax");
}

void gen_writeeflags_u64(Node *node) {
  gen_expr(node->lhs);
  println("  pushq $%ld", (int64_t)node->lhs->val);
  println("  popfq");
}

void gen_incsspq(Node *node) {
  gen_expr(node->lhs);
  println("  incsspq %%rax");
}

void gen_rstorssp(Node *node) {
  gen_addr(node->lhs);
  println("  rstorssp (%%rax)");
}

void gen_wrssd(Node *node) {
  gen_expr(node->rhs);
  println("  movq %%rax, %%rdx");
  gen_expr(node->lhs);
  println("  wrssd %%eax, (%%rdx)");
}

void gen_wrssq(Node *node) {
  gen_expr(node->rhs);
  println("  movq %%rax, %%rdx");
  gen_expr(node->lhs);
  println("  wrssq %%rax, (%%rdx)");
}

void gen_wrussd(Node *node) {
  gen_expr(node->rhs);
  println("  movq %%rax, %%rdx");
  gen_expr(node->lhs);
  println("  wrussd %%eax, (%%rdx)");
}

void gen_wrussq(Node *node) {
  gen_expr(node->rhs);
  println("  movq %%rax, %%rdx");
  gen_expr(node->lhs);
  println("  wrussq %%rax, (%%rdx)");
}

void gen_clrssbsy(Node *node) {
  gen_expr(node->lhs);
  if (node->lhs->kind == ND_NUM)
    println("  clrssbsy %ld", (int64_t)node->lhs->val);
  else
    println("  clrssbsy (%%rax)");
}

void gen_sbb_u32(Node *node) { 
  gen_expr(node->builtin_args[0]);
  println("  movl %%eax, %%edi");     // edi = bin (borrow-in)
  gen_expr(node->builtin_args[1]);
  println("  movl %%eax, %%esi");     // esi = a
  gen_expr(node->builtin_args[2]);
  println("  movl %%eax, %%edx");     // edx = b
  gen_expr(node->builtin_args[3]);
  println("  movq %%rax, %%rcx");     // rcx = out ptr
  println("  movl %%esi, %%eax");     // eax = a
  println("  bt $0, %%edi");          // CF = borrow-in bit0
  println("  sbbl %%edx, %%eax");     // eax = a - b - bin
  println("  setc %%dl");
  println("  movzbl %%dl, %%edx");
  println("  movl %%edx, (%%rcx)");   // *out = borrow
}

void gen_sbb_u64(Node *node) { 
  gen_expr(node->builtin_args[0]);
  push_tmp();                       // bin -> stack
  gen_expr(node->builtin_args[1]);
  push_tmp();                       // x -> stack
  gen_expr(node->builtin_args[2]);
  push_tmp();                       // y -> stack
  gen_expr(node->builtin_args[3]);
  println("  movq %%rax, %%rcx");    // rcx = out ptr
  pop_tmp("%rdx");                  // y
  pop_tmp("%rsi");                  // x
  pop_tmp("%rdi");                  // bin
  println("  movq %%rsi, %%rax");    // rax = x
  println("  subq %%rdx, %%rax");    // rax = x-y, CF = borrow1
  println("  setc %%r9b");           // r9b = borrow1
  println("  movq %%rdi, %%r8");     // r8 = bin
  println("  subq %%r8, %%rax");     // rax = (x-y)-bin, CF = borrow2 (independent sub)
  println("  setc %%r10b");          // r10b = borrow2
  println("  movq %%rax, (%%rcx)");  // *out = (x-y)-bin (store before clobbering rax)
  println("  orb %%r9b, %%r10b");    // r10b = borrow1 | borrow2 (reference semantics)
  println("  movzbl %%r10b, %%eax"); // eax = returned borrow
}

void gen_addcarryx_u32(Node *node) { 
  gen_expr(node->builtin_args[0]);
  push_tmp();                       // cin -> stack (callee-saved across next evals)
  gen_expr(node->builtin_args[1]);
  push_tmp();                       // x -> stack
  gen_expr(node->builtin_args[2]);
  push_tmp();                       // y -> stack
  gen_expr(node->builtin_args[3]);
  println("  movq %%rax, %%rcx");    // rcx = out ptr
  pop_tmp("%rdx");                  // y
  pop_tmp("%rsi");                  // x
  pop_tmp("%rdi");                  // cin (low byte in dil)
  println("  movl %%esi, %%eax");    // eax = x
  println("  addl %%edx, %%eax");    // eax = x+y, CF = carry1
  println("  setc %%r9b");           // r9b = carry1
  println("  movzx %%dil, %%edi");   // edi = cin (zero-extended)
  println("  addl %%edi, %%eax");    // eax = (x+y)+cin (the sum)
  println("  setc %%r10b");          // r10b = carry2
  println("  movl %%eax, (%%rcx)");  // *out = sum (store before clobbering eax)
  println("  orb %%r9b, %%r10b");    // r10b = carry1 | carry2 (reference semantics)
  println("  movzbl %%r10b, %%eax"); // eax = returned carry
}

void gen_addcarryx_u64(Node *node) { 
  gen_expr(node->builtin_args[0]);
  push_tmp();                       // cin -> stack
  gen_expr(node->builtin_args[1]);
  push_tmp();                       // x -> stack
  gen_expr(node->builtin_args[2]);
  push_tmp();                       // y -> stack
  gen_expr(node->builtin_args[3]);
  println("  movq %%rax, %%rcx");    // rcx = out ptr
  pop_tmp("%rdx");                  // y
  pop_tmp("%rsi");                  // x
  pop_tmp("%rdi");                  // cin
  println("  movq %%rsi, %%rax");    // rax = x
  println("  addq %%rdx, %%rax");    // rax = x+y, CF = carry1
  println("  setc %%r9b");           // r9b = carry1
  println("  movq %%rdi, %%r8");     // r8 = cin
  println("  addq %%r8, %%rax");     // rax = (x+y)+cin (the sum)
  println("  setc %%r10b");          // r10b = carry2
  println("  movq %%rax, (%%rcx)");  // *out = sum (store before clobbering rax)
  println("  orb %%r9b, %%r10b");    // r10b = carry1 | carry2
  println("  movzbl %%r10b, %%eax"); // eax = returned carry
}

// CAS/Atomic functions (Group H)

void gen_cas(Node *node)   {
  if (node->cas_addr->ty->base->size == 16) {
    gen_expr(node->cas_addr);
    push_tmp();
    if (node->cas_new->ty && node->cas_new->ty->kind == TY_LDOUBLE && node->cas_new->kind == ND_VAR) {
        gen_addr(node->cas_new);
        println("  mov 8(%%rax), %%rdx");
        println("  mov (%%rax), %%rax");
    } else {
        gen_expr(node->cas_new);
        if (node->cas_new->ty && node->cas_new->ty->kind == TY_LDOUBLE) {
             println("  sub $16, %%rsp");
             println("  fstpt (%%rsp)");
             println("  pop %%rax");
             println("  pop %%rdx");
        }
    }
    pushx_tmp();
    gen_expr(node->cas_old);
    println("  mov %%rax, %%r9");
    println("  mov (%%r9), %%rax");
    println("  mov 8(%%r9), %%rdx");
    
    popx_tmp("%rbx", "%rcx"); // new -> rcx:rbx
    pop_tmp("%rdi"); // addr

    println("  lock cmpxchg16b (%%rdi)");
    println("  sete %%cl");
    println("  je 1f");
    println("  mov %%rax, (%%r9)");
    println("  mov %%rdx, 8(%%r9)");
    println("1:");
    println("  movzbl %%cl, %%eax");
    return;
  }

  gen_expr(node->cas_addr);
  push_tmp();
  gen_expr(node->cas_new);
  push_tmp();
  gen_expr(node->cas_old);
  println("  mov %%rax, %%r9");
  if (!node->cas_old->ty->base)
    error("%s:%d: in %s: node->cas_old base type is null!", __FILE__, __LINE__, __func__); 
  load(node->cas_old->ty->base);
  pop_tmp("%rdx"); // new
  pop_tmp("%rdi"); // addr
  if (!node->cas_addr->ty->base)
    error("%s:%d: in %s: node->cas_addr base type is null!", __FILE__, __LINE__, __func__);   
  int sz = node->cas_addr->ty->base->size;
  println("  lock cmpxchg %s, (%%rdi)", reg_dx(sz));
  println("  sete %%cl");
  println("  je 1f");
  println("  mov %s, (%%r9)", reg_ax(sz));
  println("1:");
  println("  movzbl %%cl, %%eax");
  return;
  }

void gen_bool_cas(Node *node) {
  gen_expr(node->cas_ptr);      
  push_tmp();
  gen_expr(node->cas_expected);  
  if (node->cas_ptr->ty->base->size == 16) {
    pushx_tmp();
    gen_expr(node->cas_desired);
    if (node->cas_desired->ty && node->cas_desired->ty->kind == TY_LDOUBLE) {
        println("  sub $16, %%rsp");
        println("  fstpt (%%rsp)");
        println("  pop %%rax");
        println("  pop %%rdx");
    }
    
    println("  mov %%rax, %%rbx");
    println("  mov %%rdx, %%rcx");
    
    popx_tmp("%rax", "%rdx"); // expected -> rdx:rax
    pop_tmp("%rdi"); // addr

    println("  lock cmpxchg16b (%%rdi)");
    println("  sete %%al");
    println("  movzbl %%al, %%eax");
    return;
  }
  push_tmp();
  gen_expr(node->cas_desired);   
  push_tmp();
  pop_tmp("%rdx");
  pop_tmp("%rax");
  pop_tmp("%rdi");
  int sz = node->cas_ptr->ty->base->size;
  if (!node->cas_ptr->ty->base)
    error("%s:%d: in %s: node->cas_ptr base type is null!", __FILE__, __LINE__, __func__);   
  println("  lock cmpxchg %s, (%%rdi)", reg_dx(sz)); 
  println("  sete %%al");       
  println("  movzbl %%al, %%eax"); 
}

void gen_add_and_fetch(Node *node) {
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  if (node->lhs->ty->base->size == 16) {
    println("  mov %%rax, %%r9"); // val low
    println("  mov %%rdx, %%r11"); // val high
    pop_tmp("%rdi"); // addr

    println("  mov (%%rdi), %%rax"); // old low
    println("  mov 8(%%rdi), %%rdx"); // old high

    println("1:");
    println("  mov %%rax, %%rbx");
    println("  add %%r9, %%rbx");
    println("  mov %%rdx, %%rcx");
    println("  adc %%r11, %%rcx");

    println("  lock cmpxchg16b (%%rdi)");
    println("  jnz 1b");

    println("  mov %%rbx, %%rax");
    println("  mov %%rcx, %%rdx");
    return;
  }
  pop_tmp("%rdi");  
  int sz = node->lhs->ty->base->size;
  println("  mov %%rax, %%rcx");           
  println("  lock xadd %s, (%%rdi)", reg_ax(sz));
  println("  add %%rcx, %%rax");
  if (sz == 1)
    println("  movzbl %%al, %%eax");
  else if (sz == 2)
    println("  movzwl %%ax, %%eax");
 }

void gen_sub_and_fetch(Node *node) {
  gen_expr(node->lhs);    
  push_tmp();
  gen_expr(node->rhs);    
  if (node->ty->size == 16) {
    println("  mov %%rax, %%r9"); // val low
    println("  mov %%rdx, %%r11"); // val high
    pop_tmp("%rdi"); // addr

    println("  mov (%%rdi), %%rax"); // old low
    println("  mov 8(%%rdi), %%rdx"); // old high

    println("1:");
    println("  mov %%rax, %%rbx");
    println("  sub %%r9, %%rbx");
    println("  mov %%rdx, %%rcx");
    println("  sbb %%r11, %%rcx");

    println("  lock cmpxchg16b (%%rdi)");
    println("  jnz 1b");

    println("  mov %%rbx, %%rax");
    println("  mov %%rcx, %%rdx");
    return;
  }
  push_tmp();
  pop_tmp("%rax");        
  pop_tmp("%rdi");        
  int sz = node->lhs->ty->base->size;
  println("  mov %s, %s", reg_ax(sz), reg_cx(sz));               
  println("  neg %s", reg_ax(sz));               
  println("  lock xadd %s, (%%rdi)", reg_ax(sz));
  println("  sub %s, %s", reg_cx(sz), reg_ax(sz));      
  if (sz == 1)
    println("  movzbl %%al, %%eax");
  else if (sz == 2)
    println("  movzwl %%ax, %%eax");
}

void gen_fetchnand(Node *node) {
    gen_expr(node->lhs);  
    push_tmp();
    gen_expr(node->rhs);  
    
    if (node->lhs->ty->base->size == 16) {
        println("  mov %%rax, %%r9"); // val low
        println("  mov %%rdx, %%r11"); // val high
        pop_tmp("%rdi"); // addr

        println("  mov (%%rdi), %%rax"); // old low
        println("  mov 8(%%rdi), %%rdx"); // old high

        println("1:");
        println("  mov %%rax, %%rbx");
        println("  mov %%rdx, %%rcx");
        
        println("  and %%r9, %%rbx");
        println("  and %%r11, %%rcx");
        println("  not %%rbx");
        println("  not %%rcx");

        println("  lock cmpxchg16b (%%rdi)");
        println("  jnz 1b");

        if (node->kind == ND_NANDFETCH) {
            println("  mov %%rbx, %%rax");
            println("  mov %%rcx, %%rdx");
        }
        return;
    }

    println("  mov %%rax, %%rsi");   
    pop_tmp("%rdi");
    int sz = node->lhs->ty->base->size;
    switch(sz) {
        case 1: println("  movzbl (%%rdi), %%rax"); break;
        case 2: println("  movzwl (%%rdi), %%rax"); break;
        case 4: println("  movl (%%rdi), %%eax");   break;
        case 8: println("  movq (%%rdi), %%rax");   break;
        default: error("%s:%d: in %s: unsupported size %d!", __FILE__, __LINE__, __func__, sz); 
    }
    int label = count();
    println(".L.fetchnand_loop_%d:", label);
    println("  mov %%rax, %%rdx");  
    println("  and %%rsi, %%rdx");  
    println("  not %%rdx");         
    println("  lock cmpxchg %s, (%%rdi)", reg_dx(sz));
    println("  jnz .L.fetchnand_loop_%d", label);

    if (node->kind == ND_NANDFETCH)
        println("  mov %%rdx, %%rax"); 
}

void gen_cas_n(Node *node)   {  
  gen_expr(node->cas_addr);
  push_tmp();
  gen_expr(node->cas_new);  
  if (node->cas_new->ty && node->cas_new->ty->kind == TY_LDOUBLE) {
      println("  sub $16, %%rsp");
      println("  fstpt (%%rsp)");
      println("  pop %%rax");
      println("  pop %%rdx");
  }
  if (node->cas_addr->ty && node->cas_addr->ty->base && node->cas_addr->ty->base->size == 16) {
    pushx_tmp();
    gen_expr(node->cas_old);
    if (node->cas_old->ty && node->cas_old->ty->kind == TY_LDOUBLE) {
        println("  sub $16, %%rsp");
        println("  fstpt (%%rsp)");
        println("  pop %%rax");
        println("  pop %%rdx");
    }
    
    // old is in rdx:rax
    
    popx_tmp("%rbx", "%rcx"); // new -> rcx:rbx
    pop_tmp("%rdi"); // addr

    println("  lock cmpxchg16b (%%rdi)");
    // result (old value) is in rdx:rax, which is what we want to return
    return;
  }
  push_tmp();
  gen_expr(node->cas_old); 

  pop_tmp("%rdx"); /* new */
  pop_tmp("%rdi"); /* addr */
  int sz = node->cas_addr->ty->base->size;
  if (!node->cas_addr->ty->base)
    error("%s:%d: in %s: node->cas_addr base type is null!", __FILE__, __LINE__, __func__); 

  println("  lock cmpxchg %s, (%%rdi)", reg_dx(sz));

  {
    Type *bt = node->cas_old->ty;

    switch (bt->kind) {
    case TY_BOOL:
      println("  movzx %%al, %%eax");
      break;
    case TY_CHAR:
      if (bt->is_unsigned)
        println("  movzbl %%al, %%eax");
      else
        println("  movsbl %%al, %%eax");
      break;
    case TY_SHORT:
      if (bt->is_unsigned)
        println("  movzwl %%ax, %%eax");
      else
        println("  movswl %%ax, %%eax");
      break;
    default:
      break;
    }
  }

  return;
}

void gen_single_binop(const char *insn) {
  println("  %s", insn);
}

void gen_cvt_binop(Node *node, const char *insn) {
  gen_addr(node->lhs);    
  if (node->lhs->kind == ND_VAR || node->lhs->kind == ND_MEMBER) {
      println("  %s (%%rax), %%rax", insn);   
  } else {
      println("  %s %%xmm0, %%rax", insn);   
  }
}

void gen_atomic_is_lock_free(Node *node) {
  gen_expr(node->lhs);
  int label = count();
  println("  cmp $0, %%rax");
  println("  jle .L.not_lock_free.%d", label);
  println("  cmp $8, %%rax");
  println("  jle .L.lock_free.%d", label);
  println(".L.not_lock_free.%d:", label);
  println("  mov $0, %%rax");
  println("  jmp .L.lock_free_done.%d", label);
  println(".L.lock_free.%d:", label);
  println("  mov $1, %%rax");
  println(".L.lock_free_done.%d:", label);
}

// ============================================================
// Phase 3: SSE store/load/move (Group D) and SSE binop helpers (Group F)
// Dependencies: push_xmm, pop_xmm (now non-static)
// ============================================================

void gen_store_binop(Node *node, const char *insn) {
  gen_expr(node->rhs);
  push_xmm(0);
  gen_expr(node->lhs);
  pop_xmm(0);
  println("  %s %%xmm0, (%%rax)", insn); 
}

void gen_loadlps(Node *node) {
  gen_expr(node->lhs);
  push_xmm(0);
  gen_expr(node->rhs);
  pop_xmm(0);
  println("  movlps (%%rax), %%xmm0");
}

void gen_stmxcsr(Node *node) {
  if (node->lhs) {
    gen_expr(node->lhs); 
    println("  stmxcsr (%%rax)"); 
  } else {
    println("  stmxcsr -8(%%rsp)");  
    println("  mov -8(%%rsp), %%eax");
  }
} 

void gen_single_addr_binop(Node *node, const char *insn){
  gen_addr(node->lhs);    
  println("  %s (%%rax)", insn);
}

void gen_parity(Node *node) {
  gen_expr(node->lhs);
  if (node->lhs->kind == ND_NUM) {
    uint64_t x = node->lhs->val;  
    x ^= x >> 32;
    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;
    int parity = x & 1;
    println("  mov $%d, %%eax", parity); 

  } else {
    println("  mov %%rax, %%rcx");   // copy to rcx
    println("  shr $32, %%rcx");
    println("  xor %%rcx, %%rax");
    println("  mov %%rax, %%rcx");
    println("  shr $16, %%rcx");
    println("  xor %%rcx, %%rax");
    println("  mov %%rax, %%rcx");
    println("  shr $8, %%rcx");
    println("  xor %%rcx, %%rax");
    println("  mov %%rax, %%rcx");
    println("  shr $4, %%rcx");
    println("  xor %%rcx, %%rax");
    println("  mov %%rax, %%rcx");
    println("  shr $2, %%rcx");
    println("  xor %%rcx, %%rax");
    println("  mov %%rax, %%rcx");
    println("  shr $1, %%rcx");
    println("  xor %%rcx, %%rax");
    println("  and $1, %%eax");  // final parity in eax

  }
}

void gen_mwait(Node *node) {
  gen_expr(node->builtin_args[0]); 
  push_tmp();
  gen_expr(node->builtin_args[1]); 
  push_tmp();
  pop_tmp("%rcx");
  pop_tmp("%rax");
  println("mwait");
}

void gen_monitor(Node *node) {
  gen_expr(node->builtin_args[0]); 
  push_tmp();

  gen_expr(node->builtin_args[1]); 
  push_tmp();

  gen_expr(node->builtin_args[2]); 
  push_tmp();
  pop_tmp("%rdx");
  pop_tmp("%rcx");
  pop_tmp("%rax");
  println("monitor");
}

void gen_movq128(Node *node) {
  gen_expr(node->lhs); 
  println("  movq %%xmm0, %%xmm1");  
  println("  pxor %%xmm0, %%xmm0");  
  println("  movq %%xmm1, %%xmm0");  
}

void gen_movnti(Node *node) {
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  if (node->rhs->kind == ND_NUM)
    println("  mov $%ld, %%ecx", (int64_t)node->rhs->val);
  else 
    println("  movq (%%rax), %%rcx");
  pop_tmp("%rax");
  println("  movnti %%ecx, (%%rax)"); 
}

void gen_movnti64(Node *node) {
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  if (node->rhs->kind == ND_NUM)
    println("  mov $%ld, %%rcx", (int64_t)node->rhs->val);
  else 
    println("  movq (%%rax), %%rcx");
  pop_tmp("%rax");
  println("  movnti %%rcx, (%%rax)"); 
}

void gen_movnt_binop(Node *node, const char *insn) {
  gen_expr(node->rhs);
  push_xmm(0);
  gen_expr(node->lhs);
  pop_xmm(0);
  int c = count();
  println("  test $15, %%rax");
  println("  jnz .L.movnt_unaligned.%d", c);
  println("  %s %%xmm0, (%%rax)", insn);
  println("  jmp .L.movnt_done.%d", c);
  println(".L.movnt_unaligned.%d:", c);
  // movnt* faults on unaligned memory; fall back to unaligned SSE store.
  if (!strcmp(insn, "movntpd"))
    println("  movupd %%xmm0, (%%rax)");
  else
    println("  movdqu %%xmm0, (%%rax)");
  println(".L.movnt_done.%d:", c);
}

void gen_movntdqa(Node *node) {
  gen_expr(node->lhs);
  int c = count();
  println("  test $15, %%rax");
  println("  jnz .L.movntdqa_unaligned.%d", c);
  println("  movntdqa (%%rax), %%xmm0");
  println("  jmp .L.movntdqa_done.%d", c);
  println(".L.movntdqa_unaligned.%d:", c);
  // movntdqa faults on unaligned memory; fall back to unaligned load.
  println("  movdqu (%%rax), %%xmm0");
  println(".L.movntdqa_done.%d:", c);
}

// SSE binop helpers (Group F)

void gen_sse_binop1(Node *node, const char *insn, bool rhs_is_imm) {
  gen_expr(node->rhs);
  println("  movss %%xmm0, %%xmm1"); 
  gen_expr(node->lhs);
  println("  %s %%xmm1, %%xmm0", insn);
}

void gen_sse_binop2(Node *node, const char *insn, const char *reg, bool rhs_is_imm) {
  gen_expr(node->lhs);
  println("  %s %%xmm0, %%%s", insn, reg);  
}

void gen_sse_binop3(Node *node, const char *insn, bool rhs_is_imm) {
  gen_expr(node->rhs);
  push_xmm(0);
  gen_expr(node->lhs);
  pop_xmm(1);
  println("  %s %%xmm1, %%xmm0", insn);
}

void gen_sse_binop4(Node *node, const char *insn, const char *insn2) {
  gen_expr(node->lhs);
  push_xmm(0);
  gen_expr(node->rhs);
  pop_xmm(1);
  println("  %s %%xmm0, %%xmm1", insn); 
  println("  %s %%al", insn2);
  println("  movzx %%al, %%eax");
}

void gen_sse_binop5(Node *node, const char *insn, const char *insn2) {
  gen_expr(node->lhs);
  push_xmm(0);
  gen_expr(node->rhs);
  pop_xmm(1);
  println("  %s %%xmm1, %%xmm0", insn); 
  println("  %s %%al", insn2);
  println("  movzx %%al, %%eax");
}

void gen_sse_binop6(Node *node, const char *insn, const char *insn2) {
  gen_expr(node->lhs);
  push_xmm(0);
  gen_expr(node->rhs);
  pop_xmm(1);
  println("  %s %%xmm0, %%xmm1", insn); 
  println("  setnp %%dl");
  println("  %s %%al", insn2);
  println("  and %%al, %%dl");
  println("  movzx %%dl, %%eax");
}

void gen_sse_binop7(Node *node, const char *insn) {
  gen_expr(node->lhs);
  push_xmm(0);
  gen_expr(node->rhs);
  pop_xmm(1);
  println("  %s %%xmm0, %%xmm1", insn);  
  println("  movdqu %%xmm1, %%xmm0");  
}

void gen_sse_binop8(Node *node, const char *insn, const char *reg) {
  gen_expr(node->lhs);
  println("  movq (%%rax), %%xmm0");
  println("  %s %%xmm0, %%%s", insn, reg);  
}

void gen_sse_binop9(Node *node, const char *insn) {
  gen_expr(node->lhs);  
  push_xmm(0);
  gen_expr(node->rhs); 
  pop_xmm(1);
  println("  %s %%xmm1, %%xmm0", insn);
}

void gen_sse_binop10(Node *node, const char *insn, const char *reg) {
  gen_expr(node->lhs); 
  println("  movq %%rax, %%rdi");    
  gen_expr(node->rhs);  
  println("  %s %%%s, (%%rdi)", insn, reg);    
}

void gen_sse_binop11(Node *node, const char *insn, const char *reg) {
  gen_expr(node->lhs); 
  println("  movq %%rax, %%rdi");    
  gen_expr(node->rhs);  
  println("  %s %%%s, %%xmm0", insn, reg);  
}

void gen_sse_binop12(Node *node, const char *insn) {
  gen_expr(node->lhs); 
  println("  movaps %%xmm0, %%xmm1");   
  println("  %s  %%xmm0, %%xmm1", insn);  
}

void gen_lddqu(Node *node) {
    gen_addr(node->lhs);       
    println("  lddqu (%%rax), %%xmm0");
}

// ============================================================
// Phase 4a: Vector/Shuffle/Init (Group I)
// ============================================================

void gen_signbit(Node *node) {  
  gen_expr(node->lhs);
  switch (node->lhs->ty->kind) {
  case TY_FLOAT:
    println("  movd %%xmm0, %%eax");
    println("  shr $31, %%eax");
    return;
  case TY_DOUBLE:
    println("  movmskpd %%xmm0, %%eax"); 
    println("  and $1, %%eax");         
    return;
  case TY_LDOUBLE:
    println("  sub $16, %%rsp");
    println("  fstpt (%%rsp)");
    println("  movb 9(%%rsp), %%al");
    println("  shr $7, %%al");
    println("  movzbl %%al, %%eax");
    println("  add $16, %%rsp");
    return;
  default:
    unreachable();
  }
}

void gen_isunordered(Node *node) {
  if (node->lhs->ty && node->rhs->ty && (node->lhs->ty->kind == TY_LDOUBLE || node->rhs->ty->kind == TY_LDOUBLE)) {
    gen_expr(node->lhs);
    pushld();
    gen_expr(node->rhs);
    popld();
    println("  fucomip");
    println("  fstp %%st(0)");
    println("  setp %%al");
    println("  movzx %%al, %%eax");
    return;
  }
  gen_expr(node->lhs);
  push_tmpf();
  gen_expr(node->rhs);
  pop_tmpf(1);
  if (node->lhs->ty->kind == TY_DOUBLE)
    println("  ucomisd %%xmm1, %%xmm0");
  else
    println("  ucomiss %%xmm1, %%xmm0");
  println("  setp %%al");
  println("  movzx %%al, %%eax");
  return;
}

void gen_vec_init_v2si(Node *node) {
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  pop_tmp("%rdx");
  println("  shl $32, %%rax");    
  println("  or %%rdx, %%rax");  
  println("  movq %%rax, %%xmm0");
}

 void gen_vec_ext(Node *node) {
  gen_expr(node->lhs);
  bool ymm = (node->kind == ND_VECEXTV8SI);
  if (ymm)
    push_ymm(0);
  else
    push_xmm(0);
  gen_expr(node->rhs);
  println("  movslq %%eax, %%rcx");
  if (node->kind == ND_VECEXTV16QI) {
    println("  and $15, %%ecx");
    println("  movzbl (%%rsp,%%rcx), %%eax");
  } else if (node->kind == ND_VECEXTV8HI) {
    println("  and $7, %%ecx");
    println("  movswl (%%rsp,%%rcx,2), %%eax");
  } else if (node->kind == ND_VECEXTV4HI) {
    println("  and $3, %%ecx");
    println("  movswl (%%rsp,%%rcx,2), %%eax");
  } else if (node->kind == ND_VECEXTV2DI) {
    println("  and $1, %%ecx");
    println("  movq (%%rsp,%%rcx,8), %%rax");
  } else if (ymm) {
    println("  and $7, %%ecx");
    println("  movl (%%rsp,%%rcx,4), %%eax");
  } else {
    println("  and $%d, %%ecx", node->kind == ND_VECEXTV2SI ? 1 : 3);
    println("  movl (%%rsp,%%rcx,4), %%eax");
  }
  if (ymm)
    pop_ymm(0);
  else
    pop_xmm(0);
}

void gen_vec_ext_v4sf(Node *node) {
  gen_expr(node->lhs);
  push_xmm(0);
  gen_expr(node->rhs);
  println("  movslq %%eax, %%rcx");
  println("  and $3, %%ecx");
  println("  movss (%%rsp,%%rcx,4), %%xmm0");
  println("  add $16, %%rsp");
  depth -= 2;
}

void gen_vec_set_v4hi(Node *node) {
  gen_expr(node->builtin_args[0]);
  push_xmm(0);
  gen_expr(node->builtin_args[1]);
  println("  movl %%eax, 8(%%rsp)");
  gen_expr(node->builtin_args[2]);
  println("  and $3, %%eax");
  println("  movzwl 8(%%rsp), %%ecx");
  println("  movw %%cx, (%%rsp,%%rax,2)");
  println("  movq (%%rsp), %%mm0");
  pop_xmm(0);
}

void gen_vec_set_v8hi(Node *node) {
  gen_expr(node->builtin_args[0]);
  push_xmm(0);
  println("  sub $16, %%rsp");
  depth += 2;
  gen_expr(node->builtin_args[1]);
  println("  movl %%eax, (%%rsp)");
  gen_expr(node->builtin_args[2]);
  println("  and $7, %%eax");
  println("  movzwl (%%rsp), %%ecx");
  println("  movw %%cx, 16(%%rsp,%%rax,2)");
  println("  movdqu 16(%%rsp), %%xmm0");
  println("  add $16, %%rsp");
  depth -= 2;
  pop_xmm(0);
}

void gen_vec_set_v16qi(Node *node) {
  gen_expr(node->builtin_args[0]);
  push_xmm(0);
  println("  sub $16, %%rsp");
  depth += 2;
  gen_expr(node->builtin_args[1]);
  println("  movl %%eax, (%%rsp)");
  gen_expr(node->builtin_args[2]);
  println("  and $15, %%eax");
  println("  movzbl (%%rsp), %%ecx");
  println("  movb %%cl, 16(%%rsp,%%rax,1)");
  println("  movdqu 16(%%rsp), %%xmm0");
  println("  add $16, %%rsp");
  depth -= 2;
  pop_xmm(0);
}

void gen_vec_set_v4si(Node *node) {
  gen_expr(node->builtin_args[0]);
  push_xmm(0);
  println("  sub $16, %%rsp");
  depth += 2;
  gen_expr(node->builtin_args[1]);
  println("  movl %%eax, (%%rsp)");
  gen_expr(node->builtin_args[2]);
  println("  and $3, %%eax");
  println("  movl (%%rsp), %%ecx");
  println("  movl %%ecx, 16(%%rsp,%%rax,4)");
  println("  movdqu 16(%%rsp), %%xmm0");
  println("  add $16, %%rsp");
  depth -= 2;
  pop_xmm(0);
}

void gen_vec_set_v2di(Node *node) {
  gen_expr(node->builtin_args[0]);
  push_xmm(0);
  println("  sub $16, %%rsp");
  depth += 2;
  gen_expr(node->builtin_args[1]);
  println("  movq %%rax, (%%rsp)");
  gen_expr(node->builtin_args[2]);
  println("  and $1, %%eax");
  println("  movq (%%rsp), %%rcx");
  println("  movq %%rcx, 16(%%rsp,%%rax,8)");
  println("  movdqu 16(%%rsp), %%xmm0");
  println("  add $16, %%rsp");
  depth -= 2;
  pop_xmm(0);
}

void gen_psubusb256(Node *node) {
  gen_expr(node->rhs); // B
  push_ymm(0);
  gen_expr(node->lhs); // A
  pop_ymm(1);
  println("  vpsubusb %%ymm1, %%ymm0, %%ymm0");
}

void gen_vec_init_binop(Node *node, const char *insn) {
  for (int i = 0; i < node->builtin_nargs; i++) {
    if (i == 0) {
        gen_expr(node->builtin_args[i]);  // result in %eax
        println("  movd %%eax, %%xmm0");
    } else {
        // Preserve previously packed lanes across arg evaluation.
        push_xmm(0);
        gen_expr(node->builtin_args[i]);  // result in %eax
        pop_xmm(0);
        println("  %s $%d, %%eax, %%xmm0", insn, i);
    }
  } 
}

void gen_pshufd(Node *node) {
  gen_expr(node->lhs);
  int imm = node->rhs->val;
  println("  pshufd $%d, %%xmm0, %%xmm0", imm);
}

void gen_pshufhw(Node *node) {
  gen_expr(node->lhs);
  int imm = eval(node->rhs);
  println("  pshufhw $%d, %%xmm0, %%xmm0", imm);
}

void gen_pshuflw(Node *node) {
  gen_expr(node->lhs);
  int imm = eval(node->rhs);
  println("  pshuflw $%d, %%xmm0, %%xmm0", imm);
}

void gen_pshufw(Node *node) {
  gen_expr(node->lhs);
  println("  movq (%%rax), %%mm0");
  int imm = node->rhs->val;
  println("  pshufw $%d, %%mm0, %%mm0", imm);
  println("  movq %%mm0, %%rax");
  println("  movq %%rax, %%xmm0");
  println("  emms");
}

void gen_shuf_binop(Node *node, const char *insn) {
  gen_expr(node->rhs);
  push_xmm(0);
  gen_expr(node->lhs);
  pop_xmm(1);
  println("  %s $%ld, %%xmm1, %%xmm0", insn, (int64_t)node->rhs->val);
}

void gen_round(Node *node, const char *insn) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[1]);
  push_xmm(0);
  gen_expr(node->builtin_args[0]);
  pop_xmm(1);
  println("  %s $%ld, %%xmm1, %%xmm0", insn, eval(node->builtin_args[2]));
}

void gen_psll_binop(Node *node, const char *insn) {
  gen_expr(node->lhs);
  push_xmm(0);
  gen_expr(node->rhs);
  pop_xmm(1);
  if (node->rhs->kind == ND_NUM)
    println("  %s $%ld, %%xmm1", insn, (int64_t)node->rhs->val);
  else {
    println("  movq %%rax, %%xmm0");
    println("  %s %%xmm0, %%xmm1", insn);
  }
  println("  movaps %%xmm1, %%xmm0");      
}

static int get_const_int_from_node(Node *node) {
  if (!node)
    error("%s:%d: in %s: expected constant node", __FILE__, __LINE__, __func__);
  while (true) {
    if (node->kind == ND_NUM) return node->val;
    if (node->kind == ND_CAST) { node = node->lhs; continue; }
    if (node->kind == ND_COMMA) { node = node->rhs; continue; }
    if (node->kind == ND_ASSIGN) { node = node->rhs; continue; }
    break;
  }

  error_tok(node->tok, "%s:%d: in %s: not a compile-time integer constant", __FILE__, __LINE__, __func__);
 
}

static Node *unwrap_casts(Node *node) {
  while (node && (node->kind == ND_CAST || node->kind == ND_COMMA))
    node = node->lhs;
  return node;
}

static void get_mask_values(Node *mask_node, int *vals, int expected_len) {
  mask_node = unwrap_casts(mask_node);
  if (!mask_node->var || !mask_node->var->init)
    error_tok(mask_node->tok, "%s:%d: in %s: shuffle mask must be a constant vector initializer! %d", __FILE__, __LINE__, __func__,  mask_node->kind);

  Initializer *init = mask_node->var->init;
  if (!mask_node->var->ty || !mask_node->var->ty->base)
    error_tok(mask_node->tok, "%s:%d: in %s: shuffle mask type has no base type!", __FILE__, __LINE__, __func__);
  int len = mask_node->var->ty->array_len;
  int elem_size = mask_node->var->ty->base->size;
  int expand = elem_size / 4;

  for (int i = 0; i < len; i++) {
    Initializer *elem = init->children[i];
    if (!elem) continue;
    int val = get_const_int_from_node(elem->expr);
    for (int j = 0; j < expand; j++)
      if (i * expand + j < expected_len)
        vals[i * expand + j] = val * expand + j;
  }
}

static bool decompose_shuffle_mask_from_vals(int mask[4], int *out_imm1, int *out_imm2) {
  // mask entries must be 0..7
  for (int i = 0; i < 4; i++) if (mask[i] < 0 || mask[i] > 7) return false;

  for (int comb = 0; comb < (1 << 4); comb++) {
    int idx[4];
    int ia[2] = {-1,-1}, ib[2] = {-1,-1};
    bool ok = true;

    for (int j = 0; j < 4; j++) {
      int bit = (comb >> j) & 1;
      if (mask[j] < 4) idx[j] = bit;
      else idx[j] = 2 + bit;

      if (idx[j] < 2) {
        if (ia[idx[j]] == -1) ia[idx[j]] = mask[j];
        else if (ia[idx[j]] != mask[j]) { ok = false; break; }
      } else {
        int k = idx[j] - 2;
        if (ib[k] == -1) ib[k] = mask[j] - 4;
        else if (ib[k] != mask[j] - 4) { ok = false; break; }
      }
    }
    if (!ok) continue;

    for (int t = 0; t < 2; t++) { if (ia[t] == -1) ia[t] = 0; if (ib[t] == -1) ib[t] = 0; }

    int imm1 = (ia[0] & 3) | ((ia[1] & 3) << 2) | ((ib[0] & 3) << 4) | ((ib[1] & 3) << 6);
    int imm2 = (idx[0] & 3) | ((idx[1] & 3) << 2) | ((idx[2] & 3) << 4) | ((idx[3] & 3) << 6);

    int intermediate[4];
    intermediate[0] = ia[0];
    intermediate[1] = ia[1];
    intermediate[2] = ib[0] + 4;
    intermediate[3] = ib[1] + 4;

    int final[4];
    for (int j = 0; j < 4; j++) final[j] = intermediate[(imm2 >> (2*j)) & 3];

    bool match = true;
    for (int j = 0; j < 4; j++) if (final[j] != mask[j]) { match = false; break; }
    if (!match) continue;

    *out_imm1 = imm1;
    *out_imm2 = imm2;
    return true;
  }
  return false;
}

void gen_shuffle(Node *node, const char *insn) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[0]);
  println("  movaps %%xmm0, %%xmm2");
  gen_expr(node->builtin_args[1]);
  println("  movaps %%xmm0, %%xmm1");
  println("  movaps %%xmm2, %%xmm0");
  int mask[4] = {0};
  get_mask_values(node->builtin_args[2], mask, 4);
  int imm1, imm2;
  if (decompose_shuffle_mask_from_vals(mask, &imm1, &imm2)) {
    println("  %s $%d, %%xmm1, %%xmm0", insn, imm1);
    println("  %s $%d, %%xmm0, %%xmm0", insn, imm2);
  } else {
    int single = ((mask[3] & 3) << 6) | ((mask[2] & 3) << 4) | ((mask[1] & 3) << 2) | (mask[0] & 3);
    println("  %s $%d, %%xmm1, %%xmm0", insn, single);
  }
}

void gen_maskmovq(Node *node) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[1]); 
  println("  movq (%%rax), %%mm1"); 
  gen_expr(node->builtin_args[0]);  
  println("  movq (%%rax), %%mm0");       
  gen_addr(node->builtin_args[2]); 
  println("  movq %%rax, %%rdi"); 
  println("  maskmovq %%mm1, %%mm0");
  println("  emms");
}

void gen_maskmovdqu(Node *node) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[1]); 
  println("  movdqu (%%rax), %%xmm1"); 
  gen_expr(node->builtin_args[0]);  
  println("  movdqu (%%rax), %%xmm0");       
  gen_addr(node->builtin_args[2]); 
  println("  movq %%rax, %%rdi"); 
  println("  maskmovdqu %%xmm1, %%xmm0");
}

void gen_cvtpi2ps(Node *node) {
  gen_expr(node->lhs);    
  gen_addr(node->rhs);    
  println("  movq (%%rax), %%mm0"); 
  println("  cvtpi2ps %%mm0, %%xmm0");  
  println("  emms");
} 

void gen_loadhps(Node *node) {
  gen_expr(node->lhs);
  println("  movups (%%rax), %%xmm0");
  push_xmm(0);
  gen_expr(node->rhs);
  println("  movq (%%rax), %%xmm1");
  pop_xmm(0);
  println("  movlhps %%xmm1, %%xmm0");
}

void gen_packss128_binop(Node *node, const char *insn) {
  gen_expr(node->lhs);
  push_xmm(0);
  gen_expr(node->rhs); 
  pop_xmm(1); 
  println("  %s %%xmm0, %%xmm1", insn); 
  println("  movdqu %%xmm1, %%xmm0");
}

void gen_punpck256(Node *node, const char *insn) {
  gen_expr(node->lhs);
  push_ymm(0);
  gen_expr(node->rhs);
  pop_ymm(1);
  println("  %s %%ymm0, %%ymm1, %%ymm0", insn);
}

void gen_psadbw256(Node *node) {
  gen_expr(node->lhs); // A -> ymm0
  push_ymm(0);
  gen_expr(node->rhs); // B -> ymm0
  pop_ymm(1);
  println("  vpsadbw %%ymm0, %%ymm1, %%ymm0");
}

void gen_pack256(Node *node, const char *insn) {
  gen_expr(node->lhs);
  push_ymm(0);
  gen_expr(node->rhs);
  pop_ymm(1);
  println("  %s %%ymm0, %%ymm1, %%ymm0", insn);
}

void gen_mulhw256(Node *node) {
  gen_expr(node->lhs); // A -> ymm0
  push_ymm(0);
  gen_expr(node->rhs); // B -> ymm0
  pop_ymm(1);
  println("  vpmulhw %%ymm0, %%ymm1, %%ymm0");
}

// ============================================================
// Phase 4b: AVX2/MMX/Blend/Test (Group G)
// ============================================================

void gen_sse_pblendvb128(Node *node) {
  assert(node->builtin_nargs == 3);  
  gen_expr(node->builtin_args[0]); 
  println("  movaps %%xmm0, %%xmm1"); 
  gen_expr(node->builtin_args[1]);      
  println("  movaps %%xmm0, %%xmm2"); 
  gen_expr(node->builtin_args[2]); 
  println("  pblendvb %%xmm2, %%xmm1"); 
  println("  movaps %%xmm1, %%xmm0");
}

void gen_pblendw128(Node *node) {
  assert(node->builtin_nargs == 3);
  // First source (also destination) -> xmm0
  gen_expr(node->builtin_args[0]);
  println("  movaps %%xmm0, %%xmm1");   // save first source in xmm1
  // Second source -> xmm0
  gen_expr(node->builtin_args[1]);
  println("  movaps %%xmm0, %%xmm2");   // save second source in xmm2
  // Now we have: xmm1 = first source, xmm2 = second source
  // We want to do: pblendw $imm, %%xmm2, %%xmm1 -> result in xmm1
  // But note: the instruction is: pblendw xmm1, xmm2/m128, imm8
  // So we can do: pblendw $imm, %%xmm2, %%xmm1
  // Then move the result to %%xmm0.

  // Evaluate the immediate
  int imm = eval(node->builtin_args[2]);
  // Check that imm is between 0 and 255
  if (imm < 0 || imm > 255)
    error_tok(node->builtin_args[2]->tok, "%s:%d: in %s: immediate out of range", __FILE__, __LINE__, __func__);

  println("  pblendw $%d, %%xmm2, %%xmm1", imm);
  println("  movaps %%xmm1, %%xmm0");
}

void gen_blendps(Node *node, bool is256) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[0]);
  if (is256)
    println("  vmovaps %%ymm0, %%ymm1");
  else
    println("  movaps %%xmm0, %%xmm1");
  gen_expr(node->builtin_args[1]);
  if (is256)
    println("  vmovaps %%ymm0, %%ymm2");
  else
    println("  movaps %%xmm0, %%xmm2");
  int imm = eval(node->builtin_args[2]);
  if (imm < 0 || imm > 255)
    error_tok(node->builtin_args[2]->tok, "%s:%d: in %s: immediate out of range", __FILE__, __LINE__, __func__);
  if (is256)
    println("  vblendps $%d, %%ymm2, %%ymm1, %%ymm0", imm);
  else
    println("  blendps $%d, %%xmm2, %%xmm1", imm);
  if (!is256)
    println("  movaps %%xmm1, %%xmm0");
}

void gen_blendpd(Node *node, bool is256) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[0]);
  if (is256)
    println("  vmovaps %%ymm0, %%ymm1");
  else
    println("  movaps %%xmm0, %%xmm1");
  gen_expr(node->builtin_args[1]);
  if (is256)
    println("  vmovaps %%ymm0, %%ymm2");
  else
    println("  movaps %%xmm0, %%xmm2");
  int imm = eval(node->builtin_args[2]);
  if (imm < 0 || imm > 255)
    error_tok(node->builtin_args[2]->tok, "%s:%d: in %s: immediate out of range", __FILE__, __LINE__, __func__);
  if (is256)
    println("  vblendpd $%d, %%ymm2, %%ymm1, %%ymm0", imm);
  else
    println("  blendpd $%d, %%xmm2, %%xmm1", imm);
  if (!is256)
    println("  movaps %%xmm1, %%xmm0");
}

void gen_dpps(Node *node) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[0]);
  println("  movaps %%xmm0, %%xmm1");
  gen_expr(node->builtin_args[1]);
  println("  movaps %%xmm0, %%xmm2");
  int imm = eval(node->builtin_args[2]);
  if (imm < 0 || imm > 255)
    error_tok(node->builtin_args[2]->tok, "%s:%d: in %s: immediate out of range", __FILE__, __LINE__, __func__);
  println("  dpps $%d, %%xmm2, %%xmm1", imm);
  println("  movaps %%xmm1, %%xmm0");
}

void gen_dppd(Node *node) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[0]);
  println("  movaps %%xmm0, %%xmm1");
  gen_expr(node->builtin_args[1]);
  println("  movaps %%xmm0, %%xmm2");
  int imm = eval(node->builtin_args[2]);
  if (imm < 0 || imm > 255)
    error_tok(node->builtin_args[2]->tok, "%s:%d: in %s: immediate out of range", __FILE__, __LINE__, __func__);
  println("  dppd $%d, %%xmm2, %%xmm1", imm);
  println("  movaps %%xmm1, %%xmm0");
}

void gen_insertps128(Node *node) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[0]);
  println("  movaps %%xmm0, %%xmm1");
  gen_expr(node->builtin_args[1]);
  println("  movaps %%xmm0, %%xmm2");
  int imm = eval(node->builtin_args[2]);
  if (imm < 0 || imm > 255)
    error_tok(node->builtin_args[2]->tok, "%s:%d: in %s: immediate out of range", __FILE__, __LINE__, __func__);
  println("  insertps $%d, %%xmm2, %%xmm1", imm);
  println("  movaps %%xmm1, %%xmm0");
}

void gen_mpsadbw128(Node *node) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[0]);
  println("  movaps %%xmm0, %%xmm1");
  gen_expr(node->builtin_args[1]);
  println("  movaps %%xmm0, %%xmm2");
  int imm = eval(node->builtin_args[2]);
  if (imm < 0 || imm > 255)
    error_tok(node->builtin_args[2]->tok, "%s:%d: in %s: immediate out of range", __FILE__, __LINE__, __func__);
  println("  mpsadbw $%d, %%xmm2, %%xmm1", imm);
  println("  movaps %%xmm1, %%xmm0");
}

void gen_mpsadbw256(Node *node) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[1]);
  push_ymm(0);
  gen_expr(node->builtin_args[0]);
  pop_ymm(1);
  int imm = eval(node->builtin_args[2]);
  if (imm < 0 || imm > 255)
    error_tok(node->builtin_args[2]->tok, "%s:%d: in %s: immediate out of range", __FILE__, __LINE__, __func__);
  println("  vmpsadbw $%d, %%ymm1, %%ymm0, %%ymm0", imm);
}

void gen_pblendvb256(Node *node) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[2]); // mask -> ymm0
  push_ymm(0);
  gen_expr(node->builtin_args[1]); // src2 -> ymm0
  push_ymm(0);
  gen_expr(node->builtin_args[0]); // src1 -> ymm0
  pop_ymm(2); // src2 -> ymm2
  pop_ymm(1); // mask -> ymm1
  println("  vpblendvb %%ymm1, %%ymm2, %%ymm0, %%ymm0");
}

void gen_sse_blendvpx(Node *node, const char *insn) {
  assert(node->builtin_nargs == 3);  
  gen_expr(node->builtin_args[0]); 
  println("  movups (%%rax), %%xmm1"); 
  gen_expr(node->builtin_args[1]);      
  println("  movups (%%rax), %%xmm2"); 
  gen_expr(node->builtin_args[2]); 
  println("  movups (%%rax), %%xmm0"); 
  println("  %s %%xmm0, %%xmm2, %%xmm1", insn); 
  println("  movaps %%xmm1, %%xmm0");
}

void gen_pcmpgtb256_mask(Node *node) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[2]);
  push_tmp();

  gen_expr(node->builtin_args[0]);
  push_ymm(0);
  gen_expr(node->builtin_args[1]);
  push_ymm(0);
  pop_ymm(2);
  pop_ymm(1);
  println("  vpcmpgtb %%ymm2, %%ymm1, %%ymm0");
  println("  vpmovmskb %%ymm0, %%eax");
  pop_tmp("%rcx");
  println("  andl %%ecx, %%eax");
  println("  vzeroupper");
}

void gen_pavg256(Node *node, const char *insn) {
  gen_expr(node->lhs); // A -> ymm0
  push_ymm(0);
  gen_expr(node->rhs); // B -> ymm0
  pop_ymm(1);
  println("  %s %%ymm0, %%ymm1, %%ymm0", insn);
}

void gen_pshufb256(Node *node) {
  gen_expr(node->rhs);
  push_ymm(0);
  gen_expr(node->lhs);
  push_ymm(0);
  pop_ymm(0);
  pop_ymm(1);
  println("  vpshufb %%ymm1, %%ymm0, %%ymm0");
}

void gen_avx2_256(Node *node, const char *insn) {  
  gen_expr(node->lhs);
  int64_t imm_bits = eval(node->rhs);
  if (imm_bits < 0 || imm_bits > 255 * 8)
    error_tok(node->tok, "%s:%d: in %s: immediate out of range", __FILE__, __LINE__, __func__);
  
  if (imm_bits % 8 != 0)
    error_tok(node->tok, "%s:%d: in %s: immediate must be multiple of 8", __FILE__, __LINE__, __func__);

  int64_t imm_bytes = imm_bits / 8;
  println("  %s $%ld, %%ymm0, %%ymm0", insn, imm_bytes);
}

void gen_sse2_dqshift(Node *node, const char *insn) {
  gen_expr(node->lhs);
  int64_t imm_bits = eval(node->rhs);
  if (imm_bits < 0 || imm_bits > 255 * 8)
    error_tok(node->tok, "%s:%d: in %s: immediate out of range", __FILE__, __LINE__, __func__);
  if (imm_bits % 8 != 0)
    error_tok(node->tok, "%s:%d: in %s: immediate must be multiple of 8", __FILE__, __LINE__, __func__);
  int64_t imm_bytes = imm_bits / 8;
  println("  %s $%ld, %%xmm0", insn, imm_bytes);
}

void gen_vinsertf128_si256(Node *node) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[0]);   // -> ymm0
  push_ymm(0);
  gen_expr(node->builtin_args[1]);   // -> xmm0
  push_ymm(0);
  pop_ymm(2);
  pop_ymm(1);
  Node *imm = node->builtin_args[2];
  int64_t imm8 = eval(imm);
  if (imm8 < 0 || imm8 > 1)
    error_tok(imm->tok, "%s:%d: in %s: imm must be 0 or 1", __FILE__, __LINE__, __func__);
  int val = imm8 & 1;

  println("  vinsertf128 $%d, %%xmm2, %%ymm1, %%ymm0", val);
}

void gen_avx2_permdi256(Node *node) {
  gen_expr(node->lhs);  
  println("  vpermq $%ld, %%ymm0, %%ymm0", (int64_t)eval(node->rhs));
}

void gen_permvarsi256(Node *node) {
  gen_expr(node->lhs); // X -> ymm0
  push_ymm(0);
  gen_expr(node->rhs); // Y (indices) -> ymm0
  pop_ymm(1);
  println("  vpermd %%ymm1, %%ymm0, %%ymm0");
}

void gen_avx2_psll_binop(Node *node, const char *insn) {
  gen_expr(node->lhs); // ymm0 = lhs
  if (node->rhs->kind == ND_NUM) {
    println("  %s $%ld, %%ymm0, %%ymm0", insn, (int64_t)node->rhs->val);
  } else {
    push_vec(node->lhs->ty);
    gen_expr(node->rhs);
    println("  movq %%rax, %%xmm1");
    pop_vec(node->lhs->ty, 0);
    println("  %s %%xmm1, %%ymm0, %%ymm0", insn);
  }
}

void gen_palignr128(Node *node) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[1]); // B -> xmm0
  push_xmm(0);
  gen_expr(node->builtin_args[0]); // A -> xmm0
  pop_xmm(1);
  // xmm0 = A, xmm1 = B; result = concat(A,B) >> imm
  int64_t imm_bytes = eval(node->builtin_args[2]) / 8;
  println("  palignr $%ld, %%xmm1, %%xmm0", imm_bytes);
}

void gen_palignr(Node *node) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[1]); // B -> xmm0 (stored to memory, addr in rax)
  println("  movq (%%rax), %%mm1");
  gen_expr(node->builtin_args[0]); // A -> xmm0 (stored to memory, addr in rax)
  println("  movq (%%rax), %%mm0");
  int64_t imm_bytes = eval(node->builtin_args[2]) / 8;
  println("  palignr $%ld, %%mm1, %%mm0", imm_bytes);
  println("  movq %%mm0, %%rax");
  println("  movq %%rax, %%xmm0");
  println("  emms");
}

void gen_avx2_palignr256(Node *node) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[1]); // B -> ymm0
  push_ymm(0);
  gen_expr(node->builtin_args[0]); // A -> ymm0
  pop_ymm(1);
  int64_t imm_bytes = eval(node->builtin_args[2]) / 8;
  println("  vpalignr $%ld, %%ymm1, %%ymm0, %%ymm0", imm_bytes);
}

void gen_vperm2i128_si256(Node *node) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[1]); // Y -> ymm0
  push_ymm(0);
  gen_expr(node->builtin_args[0]); // X -> ymm0
  pop_ymm(1);
  int64_t imm = eval(node->builtin_args[2]);
  println("  vperm2i128 $%ld, %%ymm1, %%ymm0, %%ymm0", imm);
}

void gen_pblendd256(Node *node) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[1]); // B -> ymm0
  push_ymm(0);
  gen_expr(node->builtin_args[0]); // A -> ymm0
  pop_ymm(1);
  int64_t imm = eval(node->builtin_args[2]);
  println("  vpblendd $%ld, %%ymm1, %%ymm0, %%ymm0", imm);
}

void gen_pmulhuw256(Node *node) {
  gen_expr(node->lhs); // A -> ymm0
  push_ymm(0);
  gen_expr(node->rhs); // B -> ymm0
  pop_ymm(1);
  println("  vpmulhuw %%ymm0, %%ymm1, %%ymm0");
}

void gen_pmaddwd256(Node *node) {
  gen_expr(node->lhs); // A -> ymm0
  push_ymm(0);
  gen_expr(node->rhs); // B -> ymm0
  pop_ymm(1);
  println("  vpmaddwd %%ymm0, %%ymm1, %%ymm0");
}

void gen_avx2_pmovmskb256(Node *node) {
  gen_expr(node->lhs);
  println("  vpmovmskb %%ymm0, %%eax");
}

void gen_andnotsi256(Node *node) {
  gen_expr(node->lhs); 
  push_ymm(0);
  gen_expr(node->rhs); // B -> ymm0
  pop_ymm(1);
  println("  vpandn %%ymm0, %%ymm1, %%ymm0");
}

void gen_vextractf128_si256(Node *node) {  
  gen_expr(node->lhs); // Source vector -> ymm0
  Node *imm_node = node->rhs;
  int64_t imm = eval(imm_node);
  if (imm < 0 || imm > 1) error_tok(imm_node->tok, "%s:%d: in %s: vextractf128 imm must be 0 or 1", __FILE__, __LINE__, __func__);
  println("  vextractf128 $%ld, %%ymm0, %%xmm0", imm);
}

void gen_si256 (Node *node) {
  gen_expr(node->lhs);
}

void gen_cvt_mmx_binop(Node *node, const char *insn) {
  gen_addr(node->lhs);   
  println("  movups (%%rax), %%xmm0"); 
  println("  %s %%xmm0, %%mm0", insn);  
  println("  movq %%mm0, %%rax");
  println("  movq %%rax, %%xmm0");
  println("  emms");
  }

void gen_cvt_sse_binop2(Node *node, const char *insn, const char *reg, bool is_address) {  
  gen_expr(node->lhs);
  push_xmm(0);
  gen_expr(node->rhs);
  pop_xmm(0);
  if (is_address)
    println("  %s (%%%s), %%xmm0", insn, reg);
  else 
    println("  %s %%%s, %%xmm0", insn, reg);
}

void gen_cvt_mmx_binop3(Node *node, const char *insn) {
  gen_expr(node->lhs);        
  println("  %s %%xmm0, %%mm0", insn);
  gen_addr(node->lhs);         
  println("  movq %%mm0, %%rax");
  println("  movq %%rax, %%xmm0"); 
  println("  emms");
}

void gen_cvt_mmx_binop4(Node *node, const char *insn) {
  gen_expr(node->lhs);    
  println("  movq (%%rax), %%mm0");    
  println("  %s %%mm0, %%xmm0", insn);
  println("  emms");
}

void gen_mmx_binop(Node *node, const char *insn, bool rhs_is_imm) {
  gen_expr(node->lhs);
  println("  movq (%%rax), %%mm0");

  if (rhs_is_imm) {
    if (node->rhs->kind == ND_NUM) {
      println("  %s $%ld, %%mm0", insn, (int64_t)node->rhs->val);
    } else {
      gen_expr(node->rhs);
      println("  movq %%rax, %%mm1");
      println("  %s %%mm1, %%mm0", insn);
    }
  } else {
    gen_expr(node->rhs);
    println("  movq (%%rax), %%mm1");
    println("  %s %%mm1, %%mm0", insn);
  }

  println("  movq %%mm0, %%rax");
  println("  movq %%rax, %%xmm0");
  println("  emms");
}

void gen_mmx_binop1(Node *node, const char *insn) {
  gen_expr(node->lhs);    
  println("  movq (%%rax), %%mm0");
  println("  %s %%mm0, %%mm0", insn);
  println("  movq %%mm0, %%rax");
  println("  movq %%rax, %%xmm0");
  println("  emms");
}

void gen_sse_testz(Node *node) {
    gen_expr(node->lhs);   // %xmm0 = M
    push_xmm(0);
    gen_expr(node->rhs);   // %xmm0 = V
    pop_xmm(1);
    // ptest performs V & M
    println("  ptest %%xmm0, %%xmm1");  // sets ZF and CF
    println("  setz %%al");             // AL = 1 if ZF=1
    println("  movzx %%al, %%eax");     // zero-extend to EAX
}

void gen_sse_testc(Node *node) {
    gen_expr(node->lhs);              // %xmm0 = M
    push_xmm(0);
    gen_expr(node->rhs);              // %xmm0 = V
    pop_xmm(1);
    // ptest xmm1, xmm0 → sets ZF/CF
    println("  ptest %%xmm0, %%xmm1"); // CF = ((V & M) != M)
    // set result based on CF
    println("  setc %%al");            // AL = 1 if CF=1
    println("  movzx %%al, %%eax");    // zero-extend to EAX
}

void gen_sse_testnzc(Node *node) {              
    gen_expr(node->rhs);   
    push_xmm(0);
    gen_expr(node->lhs);             
    pop_xmm(1);
    println("  ptest %%xmm1, %%xmm0");  
    // ptestnzc returns 1 if ZF==0 AND CF==0 (not zero and not carry)
    println("  setnz %%al");            // al = 1 if ZF==0
    println("  setnc %%cl");            // cl = 1 if CF==0
    println("  and %%cl, %%al");        // al = al & cl
    println("  movzx %%al, %%eax");     
}

void gen_pcmpistrm128(Node *node) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[0]);
  println("  movaps %%xmm0, %%xmm1");
  gen_expr(node->builtin_args[1]);
  println("  movaps %%xmm0, %%xmm2");
  int imm = eval(node->builtin_args[2]);
  if (imm < 0 || imm > 255)
    error_tok(node->builtin_args[2]->tok, "%s:%d: in %s: immediate out of range", __FILE__, __LINE__, __func__);
  println("  pcmpistrm $%d, %%xmm2, %%xmm1", imm);
}

void gen_pcmpistri128(Node *node) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[0]);
  println("  movaps %%xmm0, %%xmm1");
  gen_expr(node->builtin_args[1]);
  println("  movaps %%xmm0, %%xmm2");
  int imm = eval(node->builtin_args[2]);
  if (imm < 0 || imm > 255)
    error_tok(node->builtin_args[2]->tok, "%s:%d: in %s: immediate out of range", __FILE__, __LINE__, __func__);
  println("  pcmpistri $%d, %%xmm2, %%xmm1", imm);
  println("  mov %%ecx, %%eax");
}

void gen_pcmpestrm128(Node *node) {
  assert(node->builtin_nargs == 5);
  gen_expr(node->builtin_args[1]);
  push_tmp();
  gen_expr(node->builtin_args[3]);
  println("  mov %%eax, %%edx");
  gen_expr(node->builtin_args[0]);
  println("  movaps %%xmm0, %%xmm2");
  gen_expr(node->builtin_args[2]);
  println("  movaps %%xmm0, %%xmm1");
  pop_tmp("%rax");
  int imm = eval(node->builtin_args[4]);
  if (imm < 0 || imm > 255)
    error_tok(node->builtin_args[4]->tok, "%s:%d: in %s: immediate out of range", __FILE__, __LINE__, __func__);
  println("  pcmpestrm $%d, %%xmm2, %%xmm1", imm);
}

void gen_pcmpestri128(Node *node) {
  assert(node->builtin_nargs == 5);
  gen_expr(node->builtin_args[1]);
  push_tmp();
  gen_expr(node->builtin_args[3]);
  println("  mov %%eax, %%edx");
  gen_expr(node->builtin_args[0]);
  println("  movaps %%xmm0, %%xmm2");
  gen_expr(node->builtin_args[2]);
  println("  movaps %%xmm0, %%xmm1");
  pop_tmp("%rax");
  int imm = eval(node->builtin_args[4]);
  if (imm < 0 || imm > 255)
    error_tok(node->builtin_args[4]->tok, "%s:%d: in %s: immediate out of range", __FILE__, __LINE__, __func__);
  println("  pcmpestri $%d, %%xmm2, %%xmm1", imm);
  println("  mov %%ecx, %%eax");
}

void gen_pcmpi_flag(Node *node, const char *flag_insn, bool is_explicit) {
  if (is_explicit) {
    assert(node->builtin_nargs == 5);
    gen_expr(node->builtin_args[1]);
    push_tmp();
    gen_expr(node->builtin_args[3]);
    println("  mov %%eax, %%edx");
    gen_expr(node->builtin_args[0]);
    println("  movaps %%xmm0, %%xmm2");
    gen_expr(node->builtin_args[2]);
    println("  movaps %%xmm0, %%xmm1");
    pop_tmp("%rax");
    int imm = eval(node->builtin_args[4]);
    if (imm < 0 || imm > 255)
      error_tok(node->builtin_args[4]->tok, "%s:%d: in %s: immediate out of range", __FILE__, __LINE__, __func__);
    println("  pcmpestri $%d, %%xmm2, %%xmm1", imm);
  } else {
    assert(node->builtin_nargs == 3);
    gen_expr(node->builtin_args[0]);
    println("  movaps %%xmm0, %%xmm1");
    gen_expr(node->builtin_args[1]);
    println("  movaps %%xmm0, %%xmm2");
    int imm = eval(node->builtin_args[2]);
    if (imm < 0 || imm > 255)
      error_tok(node->builtin_args[2]->tok, "%s:%d: in %s: immediate out of range", __FILE__, __LINE__, __func__);
    println("  pcmpistri $%d, %%xmm2, %%xmm1", imm);
  }
  println("  %s %%al", flag_insn);
  println("  movzbl %%al, %%eax");
}

void gen_pclmulqdq128(Node *node) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[0]);
  println("  movaps %%xmm0, %%xmm1");
  gen_expr(node->builtin_args[1]);
  println("  movaps %%xmm0, %%xmm2");
  int imm = eval(node->builtin_args[2]);
  if (imm < 0 || imm > 255)
    error_tok(node->builtin_args[2]->tok, "%s:%d: in %s: immediate out of range", __FILE__, __LINE__, __func__);
  println("  pclmulqdq $%d, %%xmm2, %%xmm1", imm);
  println("  movaps %%xmm1, %%xmm0");
}

void gen_dpps256(Node *node) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[1]);
  push_ymm(0);
  gen_expr(node->builtin_args[0]);
  pop_ymm(1);
  int imm = eval(node->builtin_args[2]);
  if (imm < 0 || imm > 255)
    error_tok(node->builtin_args[2]->tok, "%s:%d: in %s: immediate out of range", __FILE__, __LINE__, __func__);
  println("  vdpps $%d, %%ymm1, %%ymm0, %%ymm0", imm);
}

void gen_shufpd256(Node *node) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[1]);
  push_ymm(0);
  gen_expr(node->builtin_args[0]);
  pop_ymm(1);
  int imm = eval(node->builtin_args[2]);
  if (imm < 0 || imm > 255)
    error_tok(node->builtin_args[2]->tok, "%s:%d: in %s: immediate out of range", __FILE__, __LINE__, __func__);
  println("  vshufpd $%d, %%ymm1, %%ymm0, %%ymm0", imm);
}

void gen_shufps256(Node *node) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[1]);
  push_ymm(0);
  gen_expr(node->builtin_args[0]);
  pop_ymm(1);
  int imm = eval(node->builtin_args[2]);
  if (imm < 0 || imm > 255)
    error_tok(node->builtin_args[2]->tok, "%s:%d: in %s: immediate out of range", __FILE__, __LINE__, __func__);
  println("  vshufps $%d, %%ymm1, %%ymm0, %%ymm0", imm);
}

void gen_avx_cmp(Node *node, const char *insn, bool is256) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[1]);
  if (is256)
    push_ymm(0);
  else
    push_tmpf();
  gen_expr(node->builtin_args[0]);
  if (is256)
    pop_ymm(1);
  else
    pop_tmpf(1);
  int imm = eval(node->builtin_args[2]);
  if (imm < 0 || imm > 255)
    error_tok(node->builtin_args[2]->tok, "%s:%d: in %s: immediate out of range", __FILE__, __LINE__, __func__);
  if (is256)
    println("  %s $%d, %%ymm1, %%ymm0, %%ymm0", insn, imm);
  else
    println("  %s $%d, %%xmm1, %%xmm0", insn, imm);
}

void gen_vextractf128_pd256(Node *node) {
  gen_expr(node->lhs);
  int64_t imm = eval(node->rhs);
  if (imm < 0 || imm > 1)
    error_tok(node->rhs->tok, "%s:%d: in %s: imm must be 0 or 1", __FILE__, __LINE__, __func__);
  println("  vextractf128 $%ld, %%ymm0, %%xmm0", imm);
}

void gen_vextractf128_ps256(Node *node) {
  gen_expr(node->lhs);
  int64_t imm = eval(node->rhs);
  if (imm < 0 || imm > 1)
    error_tok(node->rhs->tok, "%s:%d: in %s: imm must be 0 or 1", __FILE__, __LINE__, __func__);
  println("  vextractf128 $%ld, %%ymm0, %%xmm0", imm);
}

void gen_vinsertf128_pd256(Node *node) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[0]);
  push_ymm(0);
  gen_expr(node->builtin_args[1]);
  push_ymm(0);
  pop_ymm(2);
  pop_ymm(1);
  int64_t imm = eval(node->builtin_args[2]);
  if (imm < 0 || imm > 1)
    error_tok(node->builtin_args[2]->tok, "%s:%d: in %s: imm must be 0 or 1", __FILE__, __LINE__, __func__);
  println("  vinsertf128 $%ld, %%xmm2, %%ymm1, %%ymm0", imm);
}

void gen_vinsertf128_ps256(Node *node) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[0]);
  push_ymm(0);
  gen_expr(node->builtin_args[1]);
  push_ymm(0);
  pop_ymm(2);
  pop_ymm(1);
  int64_t imm = eval(node->builtin_args[2]);
  if (imm < 0 || imm > 1)
    error_tok(node->builtin_args[2]->tok, "%s:%d: in %s: imm must be 0 or 1", __FILE__, __LINE__, __func__);
  println("  vinsertf128 $%ld, %%xmm2, %%ymm1, %%ymm0", imm);
}

void gen_vperm2f128_si256(Node *node) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[1]);
  push_ymm(0);
  gen_expr(node->builtin_args[0]);
  pop_ymm(1);
  int64_t imm = eval(node->builtin_args[2]);
  if (imm < 0 || imm > 255)
    error_tok(node->builtin_args[2]->tok, "%s:%d: in %s: immediate out of range", __FILE__, __LINE__, __func__);
  println("  vperm2f128 $%ld, %%ymm1, %%ymm0, %%ymm0", imm);
}

void gen_vperm2f128_pd256(Node *node) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[1]);
  push_ymm(0);
  gen_expr(node->builtin_args[0]);
  pop_ymm(1);
  int64_t imm = eval(node->builtin_args[2]);
  if (imm < 0 || imm > 255)
    error_tok(node->builtin_args[2]->tok, "%s:%d: in %s: immediate out of range", __FILE__, __LINE__, __func__);
  println("  vperm2f128 $%ld, %%ymm1, %%ymm0, %%ymm0", imm);
}

void gen_vperm2f128_ps256(Node *node) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[1]);
  push_ymm(0);
  gen_expr(node->builtin_args[0]);
  pop_ymm(1);
  int64_t imm = eval(node->builtin_args[2]);
  if (imm < 0 || imm > 255)
    error_tok(node->builtin_args[2]->tok, "%s:%d: in %s: immediate out of range", __FILE__, __LINE__, __func__);
  println("  vperm2f128 $%ld, %%ymm1, %%ymm0, %%ymm0", imm);
}

void gen_vpermilpd(Node *node) {
  gen_expr(node->lhs);
  int64_t imm = eval(node->rhs);
  if (imm < 0 || imm > 255)
    error_tok(node->rhs->tok, "%s:%d: in %s: immediate out of range", __FILE__, __LINE__, __func__);
  println("  vpermilpd $%ld, %%xmm0, %%xmm0", imm);
}

void gen_vpermilps(Node *node) {
  gen_expr(node->lhs);
  int64_t imm = eval(node->rhs);
  if (imm < 0 || imm > 255)
    error_tok(node->rhs->tok, "%s:%d: in %s: immediate out of range", __FILE__, __LINE__, __func__);
  println("  vpermilps $%ld, %%xmm0, %%xmm0", imm);
}

void gen_vpermilpd256(Node *node) {
  gen_expr(node->lhs);
  int64_t imm = eval(node->rhs);
  if (imm < 0 || imm > 255)
    error_tok(node->rhs->tok, "%s:%d: in %s: immediate out of range", __FILE__, __LINE__, __func__);
  println("  vpermilpd $%ld, %%ymm0, %%ymm0", imm);
}

void gen_vpermilps256(Node *node) {
  gen_expr(node->lhs);
  int64_t imm = eval(node->rhs);
  if (imm < 0 || imm > 255)
    error_tok(node->rhs->tok, "%s:%d: in %s: immediate out of range", __FILE__, __LINE__, __func__);
  println("  vpermilps $%ld, %%ymm0, %%ymm0", imm);
}

void gen_avx512pf_void(Node *node) {
}

void gen_xabort(Node *node) {
}

void gen_vpclmulqdq_v4di(Node *node) {
  gen_expr(node->builtin_args[0]);
}

static const char *vbmi2_insn(Node *node) {
  switch (node->kind) {
    case ND_VPSHRD_V32HI: return "vpshrdw";
    case ND_VPSHRD_V16SI: return "vpshrdd";
    case ND_VPSHRD_V8DI:  return "vpshrdq";
    case ND_VPSHLD_V32HI: return "vpshldw";
    case ND_VPSHLD_V16SI: return "vpshldd";
    case ND_VPSHLD_V8DI:  return "vpshldq";
    case ND_VPSHRD_V16SI_MASK: return "vpshrdd";
    case ND_VPSHRD_V8DI_MASK:  return "vpshrdq";
    case ND_VPSHLD_V16SI_MASK: return "vpshldd";
    case ND_VPSHLD_V8DI_MASK:  return "vpshldq";
    default: error("%s:%d: in %s: not a VBMI2 node kind", __FILE__, __LINE__, __func__);
  }
}

void gen_vbmi2_3(Node *node) {
  assert(node->builtin_nargs == 3);
  Type *ty = node->builtin_args[0]->ty;

  gen_expr(node->builtin_args[1]);
  push_vec(ty);
  gen_expr(node->builtin_args[0]);
  pop_vec(ty, 1);

  int64_t imm = eval(node->builtin_args[2]);
  if (imm < 0 || imm > 255)
    error_tok(node->builtin_args[2]->tok, "%s:%d: in %s: immediate out of range", __FILE__, __LINE__, __func__);

  if (ty->size > 32)
    println("  %s $%ld, %%zmm1, %%zmm0, %%zmm0", vbmi2_insn(node), imm);
  else
    println("  %s $%ld, %%ymm1, %%ymm0, %%ymm0", vbmi2_insn(node), imm);
}

void gen_vbmi2_5(Node *node) {
  assert(node->builtin_nargs == 5);
  Type *ty = node->builtin_args[0]->ty;

  // args: [0]=a, [1]=b, [2]=imm, [3]=src(merge), [4]=k(mask)
  // We need: a in zmm0, b in zmm1, src in zmm2, k in k1
  gen_expr(node->builtin_args[3]);
  push_vec(ty);

  gen_expr(node->builtin_args[1]);
  push_vec(ty);

  gen_expr(node->builtin_args[0]);

  pop_vec(ty, 1);
  pop_vec(ty, 2);

  gen_expr(node->builtin_args[4]);
  println("  kmovw %%eax, %%k1");

  int64_t imm = eval(node->builtin_args[2]);
  if (imm < 0 || imm > 255)
    error_tok(node->builtin_args[2]->tok, "%s:%d: in %s: immediate out of range", __FILE__, __LINE__, __func__);

  if (ty->size > 32)
    println("  %s $%ld, %%zmm1, %%zmm0, %%zmm2{%k1}", vbmi2_insn(node), imm);
  else
    println("  %s $%ld, %%ymm1, %%ymm0, %%ymm2{%k1}", vbmi2_insn(node), imm);

  if (ty->size > 32)
    println("  vmovdqa64 %%zmm2, %%zmm0");
  else if (ty->size > 16)
    println("  vmovdqa %%ymm2, %%ymm0");
  else
    println("  movdqa %%xmm2, %%xmm0");
}

void gen_avx512er_first(Node *node) {
  if (node->builtin_nargs >= 4) {
    gen_expr(node->builtin_args[1]);
  } else {
    gen_expr(node->builtin_args[0]);
  }
  println("  vzeroupper");
}
