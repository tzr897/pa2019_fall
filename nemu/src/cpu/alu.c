#include "cpu/cpu.h"
#include <stdlib.h>

void set_ZF(uint32_t result,size_t data_size);
void set_SF(uint32_t result,size_t data_size);
void set_PF(uint32_t result);

//alu_add()//genghuan
void set_CF_add(uint32_t result,uint32_t src,size_t data_size);
void set_OF_add(uint32_t result,uint32_t src,uint32_t dest,size_t data_size);

//alu_adc()
void set_CF_adc(uint32_t result,uint32_t src,size_t data_size);
void set_OF_adc(uint32_t result,uint32_t src,uint32_t dest,size_t data_size);

//alu_sub()
void set_CF_sub(uint32_t result,uint32_t src,size_t data_size);
void set_OF_sub(uint32_t result,uint32_t src,uint32_t dest,size_t data_size);

//alu_sbb()
void set_CF_sbb(uint32_t result,uint32_t src,size_t data_size);
void set_OF_sbb(uint32_t result,uint32_t src,uint32_t dest,size_t data_size);

//alu_mul()
void set_CF_mul(uint64_t result,size_t data_size);


uint32_t alu_add(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_add(src, dest, data_size);
#else
	uint32_t res =0;
	res=dest+src;
	set_CF_add(res,src,data_size);
	set_PF(res);
	set_ZF(res,data_size);
	set_SF(res,data_size);
	set_OF_add(res,src,dest,data_size);
	return res&(0xFFFFFFFF>>(32-data_size));
#endif
}

uint32_t alu_adc(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_adc(src, dest, data_size);
#else
	uint32_t res=0;
	res=dest+src+cpu.eflags.CF;
	set_PF(res);
	set_ZF(res,data_size);
	set_SF(res,data_size);
	set_OF_adc(res,src,dest,data_size);
	set_CF_adc(res,src,data_size);
	return res&(0xFFFFFFFF>>(32-data_size));
#endif
}

uint32_t alu_sub(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sub(src, dest, data_size);
#else
	uint32_t res =0;
	res=dest-src;
	set_CF_sub(res,src,data_size);
	set_PF(res);
	set_ZF(res,data_size);
	set_SF(res,data_size);
	set_OF_sub(res,src,dest,data_size);
	return res&(0xFFFFFFFF>>(32-data_size));
#endif
}

uint32_t alu_sbb(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sbb(src, dest, data_size);
#else
	uint32_t res=0;
	res=dest-src-cpu.eflags.CF;
	set_PF(res);
	set_ZF(res,data_size);
	set_SF(res,data_size);
	set_OF_sbb(res,src,dest,data_size);
	set_CF_sbb(res,src,data_size);
	
	
	return res&(0xFFFFFFFF>>(32-data_size));
#endif
}

uint64_t alu_mul(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_mul(src, dest, data_size);
#else
	uint64_t src64=src,dest64=dest;
	uint64_t res;
	res=dest64*src64;
	set_CF_mul(res,data_size);
	cpu.eflags.OF=cpu.eflags.CF;
	return res;
#endif
}

int64_t alu_imul(int32_t src, int32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_imul(src, dest, data_size);
#else
	int64_t res;
	int64_t src64=src;
	int64_t dest64=dest;
	res=src64*dest64;
	return res;
#endif
}

// need to implement alu_mod before testing
uint32_t alu_div(uint64_t src, uint64_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_div(src, dest, data_size);
#else
	uint64_t res=0;
	uint32_t res32=0;
	if(src==0)
	{
		abort();
	}
	else
	{
		res=dest/src;
		res32=res;
		return res32;
	}
#endif
}

// need to implement alu_imod before testing
int32_t alu_idiv(int64_t src, int64_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_idiv(src, dest, data_size);
#else
	int32_t res;
	if(src==0)
	{
		abort();
	}
	else
	{
		res=dest/src;
		return res;
	}
#endif
}

uint32_t alu_mod(uint64_t src, uint64_t dest)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_mod(src, dest);
#else
	uint64_t res;
	uint32_t res32;
	res=dest%src;
	res32=res;
	return res32;
#endif
}

int32_t alu_imod(int64_t src, int64_t dest)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_imod(src, dest);
#else
	int32_t res;
	res=dest%src;
	return res;
#endif
}

uint32_t alu_and(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_and(src, dest, data_size);
#else
	uint32_t res;
	res=(src&dest);
	res=res&(0xFFFFFFFF>>(32-data_size));
	set_PF(res);
	set_ZF(res,data_size);
	set_SF(res,data_size);
	return res;
#endif
}

uint32_t alu_xor(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_xor(src, dest, data_size);
#else
	uint32_t res;
	res=(src^dest);
	res=res&(0xFFFFFFFF>>(32-data_size));
	set_PF(res);
	set_ZF(res,data_size);
	set_SF(res,data_size);
	return res;
#endif
}

uint32_t alu_or(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_or(src, dest, data_size);
#else
	uint32_t res;
	res=(src|dest);
	res=res&(0xFFFFFFFF>>(32-data_size));
	set_PF(res);
	set_ZF(res,data_size);
	set_SF(res,data_size);
	return res;
#endif
}

uint32_t alu_shl(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_shl(src, dest, data_size);
#else
	uint32_t res;
	bool sign;
	dest=dest&(0xFFFFFFFF>>(32-data_size));
	if(src>0)
	{
		res=dest<<(src-1);
		sign=res>>(data_size-1);
		res=res<<1;
		res=res&(0xFFFFFFFF>>(32-data_size));
		set_PF(res);
		set_ZF(res,data_size);
		set_SF(res,data_size);

		cpu.eflags.CF=sign;
		return res;
	}
	else
	{
		return dest;
	}
	
	// uint32_t res,t;
	// bool sign;	
	// dest=dest&(0xFFFFFFFF>>(32-data_size));
	// //src=src&(0xFFFFFFFF>>(32-data_size));
	// res=dest<<(src-1);	
	// t=res;
	// sign=t>>(data_size-1);
	// res=t<<1;
	// res=res&(0xFFFFFFFF>>(32-data_size));

	// set_PF(res);
	// set_ZF(res,data_size);
	// set_SF(res,data_size);

	// cpu.eflags.CF=sign;
	// return res;//
#endif
}

uint32_t alu_shr(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_shr(src, dest, data_size);
#else
	uint32_t res,t;
	bool sign;
	dest=dest&(0xFFFFFFFF>>(32-data_size));
	src=src&(0xFFFFFFFF>>(32-data_size));
	res=dest>>(src-1);
	t=res;
	sign=t&0x1;
	res=res>>0x1;
	res=res&(0xFFFFFFFF>>(32-data_size));
	set_PF(res);
	set_ZF(res,data_size);
	set_SF(res,data_size);
	cpu.eflags.CF=sign;
	return res;
#endif
}

uint32_t alu_sar(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sar(src, dest, data_size);
#else
	uint32_t t,andt,res,i;
	uint32_t sign,cflag;
	dest=dest&(0xFFFFFFFF >> (32-data_size));
	src=src&(0xFFFFFFFF >> (32-data_size));
	t=dest >> (src-1);
	cflag=t & 0x1;
	t=dest;
	sign=(t >> (data_size-1))&0x1;
	andt=0x1 << (data_size-1);
	t=dest;
	if(sign==0)
	{
		res=dest >> src;
		res=res&(0xFFFFFFFF >> (32-data_size));
		
	}
	else
	{
		res=0;
		for(i=0;i<src;++i)
		{
			t=t >> 1;
			res=t|andt;
			t=res;
		}
		res=res&(0xFFFFFFFF >> (32-data_size));
	}
	set_PF(res);
	set_ZF(res,data_size);
	set_SF(res,data_size);
	cpu.eflags.CF=cflag;
	return res;
#endif
}

uint32_t alu_sal(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sal(src, dest, data_size);
#else
	uint32_t res,t;
	bool sign;	
	dest=dest&(0xFFFFFFFF>>(32-data_size));
	src=src&(0xFFFFFFFF>>(32-data_size));
	res=dest<<(src-1);	
	t=res;
	sign=t>>(data_size-1);
	res=t<<1;
	res=res&(0xFFFFFFFF>>(32-data_size));
	set_PF(res);
	set_ZF(res,data_size);
	set_SF(res,data_size);
	cpu.eflags.CF=sign;
	return res;
#endif
}
////////////////////////////////////////////////////////
//alu_add()
//CF contains information relevant to unsigned integers
void set_CF_add(uint32_t result,uint32_t src,size_t data_size)
{
	result=sign_ext(result&(0xFFFFFFFF>>(32-data_size)),data_size);
	src=sign_ext(src&(0xFFFFFFFF>>(32-data_size)),data_size);
	cpu.eflags.CF=result<src;
}

void set_ZF(uint32_t result,size_t data_size)
{
	result=result&(0xFFFFFFFF>>(32-data_size));
	cpu.eflags.ZF=(result==0);
}

//SF and OF contain information relevant to signed integers
void set_SF(uint32_t result,size_t data_size)
{
	result=sign_ext(result&(0xFFFFFFFF>>(32-data_size)),data_size);
	cpu.eflags.SF=sign(result);
}

void set_PF(uint32_t result)
{
	uint32_t i,count=8;
	for(i=1;i<=128;i*=2)
	{
		if((result&i)==0)
			count--;
	}
	if(count%2==0)
		cpu.eflags.PF=1;
	else
		cpu.eflags.PF=0;
	
}

void set_OF_add(uint32_t result,uint32_t src,uint32_t dest,size_t data_size)
{
	switch(data_size)
	{
		case 8:
			result=sign_ext(result&0xFF,8);
			src=sign_ext(src&0xFF,8);
			dest=sign_ext(dest&0xFF,8);
			break;
		case 16:
			result=sign_ext(result&0xFFFF,16);
			src=sign_ext(src&0xFFFF,16);
			dest=sign_ext(dest&0xFFFF,16);
		default:break;
	}
	if(sign(src)==sign(dest))
	{
		if(sign(src)!=sign(result))
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
	}
	else
	{
		cpu.eflags.OF=0;
	}
}

////////////////////////////////////////////////
//alu_adc()
void set_CF_adc(uint32_t result,uint32_t src,size_t data_size)
{
	result=sign_ext(result&(0xFFFFFFFF>>(32-data_size)),data_size);
	src=sign_ext(src&(0xFFFFFFFF>>(32-data_size)),data_size);
	if(cpu.eflags.CF==1)
	{
		if(result==src)
		{
			cpu.eflags.CF=1;
		}
		else
		{
			cpu.eflags.CF=result<src;
		}
		
	}
	else
	{
		cpu.eflags.CF=result<src;
	}
	
	
	
}

void set_OF_adc(uint32_t result,uint32_t src,uint32_t dest,size_t data_size)
{
	switch(data_size)
	{
		case 8:
			result=sign_ext(result&0xFF,8);
			src=sign_ext(src&0xFF,8);
			dest=sign_ext(dest&0xFF,8);
			break;
		case 16:
			result=sign_ext(result&0xFFFF,16);
			src=sign_ext(src&0xFFFF,16);
			dest=sign_ext(dest&0xFFFF,16);
		default:break;
	}
	if(cpu.eflags.CF==1)
	{
		if(result==src)
		{
			cpu.eflags.OF=0;
		}
		else
		{
			if(sign(src)==sign(dest))
			{
				if(sign(src)!=sign(result))
					cpu.eflags.OF=1;
				else
					cpu.eflags.OF=0;
			}
			else
			{
				cpu.eflags.OF=0;
			}
		}
	}
	else
	{
		if(sign(src)==sign(dest))
		{
			if(sign(src)!=sign(result))
				cpu.eflags.OF=1;
			else
				cpu.eflags.OF=0;
		}	
		else
		{
			cpu.eflags.OF=0;
		}
	}
	
	
}

/////////////////////////////////////////////////
//set_CF_sub()
void set_CF_sub(uint32_t result,uint32_t src,size_t data_size)
{
	result=sign_ext(result&(0xFFFFFFFF>>(32-data_size)),data_size);
	src=sign_ext(src&(0xFFFFFFFF>>(32-data_size)),data_size);
	cpu.eflags.CF=src>(result+src);
}

void set_OF_sub(uint32_t result,uint32_t src,uint32_t dest,size_t data_size)
{
	switch(data_size)
	{
		case 8:
			result=sign_ext(result&0xFF,8);
			src=sign_ext(src&0xFF,8);
			dest=sign_ext(dest&0xFF,8);
			break;
		case 16:
			result=sign_ext(result&0xFFFF,16);
			src=sign_ext(src&0xFFFF,16);
			dest=sign_ext(dest&0xFFFF,16);
		default:break;
	}
	if(sign(src)!=sign(dest))
	{
		if(sign(src)==sign(result))
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
	}
	else
	{
		cpu.eflags.OF=0;
	}

}

//////////////////////////////////////////
//alu_sbb()
void set_CF_sbb(uint32_t result,uint32_t src,size_t data_size)
{
	result=sign_ext(result&(0xFFFFFFFF>>(32-data_size)),data_size);
	src=sign_ext(src&(0xFFFFFFFF>>(32-data_size)),data_size);
	if(cpu.eflags.CF==1)
	{
		if(result+src+1==src)
		{
			cpu.eflags.CF=1;
		}
		else
		{
			cpu.eflags.CF=src>(result+src+1);
		}
		
	}
	else
	{
		cpu.eflags.CF=src>(result+src);
	}


}

void set_OF_sbb(uint32_t result,uint32_t src,uint32_t dest,size_t data_size)
{
	switch(data_size)
	{
		case 8:
			result=sign_ext(result&0xFF,8);
			src=sign_ext(src&0xFF,8);
			dest=sign_ext(dest&0xFF,8);
			break;
		case 16:
			result=sign_ext(result&0xFFFF,16);
			src=sign_ext(src&0xFFFF,16);
			dest=sign_ext(dest&0xFFFF,16);
		default:break;
	}
	if(cpu.eflags.CF==1)
	{
		if(result+src+1==src)
		{
			cpu.eflags.OF=0;
		}
		else
		{
			if(sign(src)!=sign(dest))
			{
				if(sign(src)==sign(result))
					cpu.eflags.OF=1;
				else
					cpu.eflags.OF=0;
			}
			else
			{
				cpu.eflags.OF=0;
			}
		}
	}
	else
	{
		if(sign(src)!=sign(dest))
		{
			if(sign(src)==sign(result))
				cpu.eflags.OF=1;
			else
				cpu.eflags.OF=0;
		}	
		else
		{
			cpu.eflags.OF=0;
		}
	}

}

////////////////////////////////////////////
//alu_mul()
void set_CF_mul(uint64_t result,size_t data_size)
{
	uint64_t t;
	t=result>>data_size;
	if(t==0)
	{
		cpu.eflags.CF=0;
	}
	else
	{
		cpu.eflags.CF=1;
	}	
}
