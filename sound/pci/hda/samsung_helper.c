// SPDX-License-Identifier: GPL-2.0-or-later
/* Helper functions for Samsung Galaxy Book3 audio initialization */

struct alc298_samsung_coeff_fixup_desc {
	unsigned char coeff_idx;
	unsigned short coeff_value;
};

struct alc298_samsung_coeff_seq_desc {
	unsigned short coeff_0x23;
	unsigned short coeff_0x24;
	unsigned short coeff_0x25;
	unsigned short coeff_0x26;
};


static inline void alc298_samsung_write_coef_pack2(struct hda_codec *codec,
						   const struct alc298_samsung_coeff_seq_desc *seq)
{
	int i;

	for (i = 0; i < 100; i++) {
		if ((alc_read_coef_idx(codec, 0x26) & 0x0010) == 0)
			break;

		usleep_range(500, 1000);
	}

	alc_write_coef_idx(codec, 0x23, seq->coeff_0x23);
	alc_write_coef_idx(codec, 0x24, seq->coeff_0x24);
	alc_write_coef_idx(codec, 0x25, seq->coeff_0x25);
	alc_write_coef_idx(codec, 0x26, seq->coeff_0x26);
}

static inline void alc298_samsung_write_coef_pack_seq(
						struct hda_codec *codec,
						unsigned char target,
						const struct alc298_samsung_coeff_seq_desc seq[],
						int count)
{
	alc_write_coef_idx(codec, 0x22, target);
	for (int i = 0; i < count; i++)
		alc298_samsung_write_coef_pack2(codec, &seq[i]);
}

static void alc298_fixup_samsung_amp2(struct hda_codec *codec,
				      const struct hda_fixup *fix, int action)
{
	int i;
	static const struct alc298_samsung_coeff_fixup_desc fixups1[] = {
		{ 0x99, 0x8000 }, { 0x82, 0x4408 }, { 0x32, 0x3f00 }, { 0x0e, 0x6f80 },
		{ 0x10, 0x0e21 }, { 0x55, 0x8000 }, { 0x08, 0x2fcf }, { 0x08, 0x2fcf },
		{ 0x2d, 0xc020 }, { 0x19, 0x0017 }, { 0x50, 0x1000 }, { 0x0e, 0x6f80 },
		{ 0x08, 0x2fcf }, { 0x80, 0x0011 }, { 0x2b, 0x0c10 }, { 0x2d, 0xc020 },
		{ 0x03, 0x0042 }, { 0x0f, 0x0062 }, { 0x08, 0x2fcf },
	};

	static const struct alc298_samsung_coeff_seq_desc amp_0x38[] = {
		{ 0x2000, 0x0000, 0x0001, 0xb011 }, { 0x23ff, 0x0000, 0x0000, 0xb011 },
		{ 0x203a, 0x0000, 0x0080, 0xb011 }, { 0x23e1, 0x0000, 0x0000, 0xb011 },
		{ 0x2012, 0x0000, 0x006f, 0xb011 }, { 0x2014, 0x0000, 0x0000, 0xb011 },
		{ 0x201b, 0x0000, 0x0001, 0xb011 }, { 0x201d, 0x0000, 0x0001, 0xb011 },
		{ 0x201f, 0x0000, 0x00fe, 0xb011 }, { 0x2021, 0x0000, 0x0000, 0xb011 },
		{ 0x2022, 0x0000, 0x0010, 0xb011 }, { 0x203d, 0x0000, 0x0005, 0xb011 },
		{ 0x203f, 0x0000, 0x0003, 0xb011 }, { 0x2050, 0x0000, 0x002c, 0xb011 },
		{ 0x2076, 0x0000, 0x000e, 0xb011 }, { 0x207c, 0x0000, 0x004a, 0xb011 },
		{ 0x2081, 0x0000, 0x0003, 0xb011 }, { 0x2399, 0x0000, 0x0003, 0xb011 },
		{ 0x23a4, 0x0000, 0x00b5, 0xb011 }, { 0x23a5, 0x0000, 0x0001, 0xb011 },
		{ 0x23ba, 0x0000, 0x0094, 0xb011 }, { 0x2100, 0x00d0, 0x950e, 0xb017 },
		{ 0x2104, 0x0061, 0xd4e2, 0xb017 }, { 0x2108, 0x00d0, 0x950e, 0xb017 },
		{ 0x210c, 0x0075, 0xf4e2, 0xb017 }, { 0x2110, 0x00b4, 0x4b0d, 0xb017 },
		{ 0x2114, 0x000a, 0x1000, 0xb017 }, { 0x2118, 0x0015, 0x2000, 0xb017 },
		{ 0x211c, 0x000a, 0x1000, 0xb017 }, { 0x2120, 0x0075, 0xf4e2, 0xb017 },
		{ 0x2124, 0x00b4, 0x4b0d, 0xb017 }, { 0x2128, 0x0000, 0x0010, 0xb017 },
		{ 0x212c, 0x0000, 0x0000, 0xb017 }, { 0x2130, 0x0000, 0x0000, 0xb017 },
		{ 0x2134, 0x0000, 0x0000, 0xb017 }, { 0x2138, 0x0000, 0x0000, 0xb017 },
		{ 0x213c, 0x0000, 0x0010, 0xb017 }, { 0x2140, 0x0000, 0x0000, 0xb017 },
		{ 0x2144, 0x0000, 0x0000, 0xb017 }, { 0x2148, 0x0000, 0x0000, 0xb017 },
		{ 0x214c, 0x0000, 0x0000, 0xb017 }, { 0x2150, 0x0000, 0x0010, 0xb017 },
		{ 0x2154, 0x0000, 0x0000, 0xb017 }, { 0x2158, 0x0000, 0x0000, 0xb017 },
		{ 0x215c, 0x0000, 0x0000, 0xb017 }, { 0x2160, 0x0000, 0x0000, 0xb017 },
		{ 0x2164, 0x0000, 0x0010, 0xb017 }, { 0x2168, 0x0000, 0x0000, 0xb017 },
		{ 0x216c, 0x0000, 0x0000, 0xb017 }, { 0x2170, 0x0000, 0x0000, 0xb017 },
		{ 0x2174, 0x0000, 0x0000, 0xb017 }, { 0x2178, 0x0000, 0x0010, 0xb017 },
		{ 0x217c, 0x0000, 0x0000, 0xb017 }, { 0x2180, 0x0000, 0x0000, 0xb017 },
		{ 0x2184, 0x0000, 0x0000, 0xb017 }, { 0x2188, 0x0000, 0x0000, 0xb017 },
		{ 0x218c, 0x0064, 0x5800, 0xb017 }, { 0x2190, 0x00c8, 0xb000, 0xb017 },
		{ 0x2194, 0x0064, 0x5800, 0xb017 }, { 0x2198, 0x003d, 0x5be7, 0xb017 },
		{ 0x219c, 0x0054, 0x060a, 0xb017 }, { 0x21a0, 0x00c8, 0xa310, 0xb017 },
		{ 0x21a4, 0x0029, 0x4de5, 0xb017 }, { 0x21a8, 0x0032, 0x420c, 0xb017 },
		{ 0x21ac, 0x0029, 0x4de5, 0xb017 }, { 0x21b0, 0x00fa, 0xe50c, 0xb017 },
		{ 0x21b4, 0x0000, 0x0010, 0xb017 }, { 0x21b8, 0x0000, 0x0000, 0xb017 },
		{ 0x21bc, 0x0000, 0x0000, 0xb017 }, { 0x21c0, 0x0000, 0x0000, 0xb017 },
		{ 0x21c4, 0x0000, 0x0000, 0xb017 }, { 0x21c8, 0x0056, 0xc50f, 0xb017 },
		{ 0x21cc, 0x007b, 0xd7e1, 0xb017 }, { 0x21d0, 0x0077, 0xa70e, 0xb017 },
		{ 0x21d4, 0x00e0, 0xbde1, 0xb017 }, { 0x21d8, 0x0032, 0x530e, 0xb017 },
		{ 0x2204, 0x00fb, 0x7e0f, 0xb017 }, { 0x2208, 0x000b, 0x02e1, 0xb017 },
		{ 0x220c, 0x00fb, 0x7e0f, 0xb017 }, { 0x2210, 0x00d5, 0x17e1, 0xb017 },
		{ 0x2214, 0x00c0, 0x130f, 0xb017 }, { 0x2218, 0x00e5, 0x0a00, 0xb017 },
		{ 0x221c, 0x00cb, 0x1500, 0xb017 }, { 0x2220, 0x00e5, 0x0a00, 0xb017 },
		{ 0x2224, 0x00d5, 0x17e1, 0xb017 }, { 0x2228, 0x00c0, 0x130f, 0xb017 },
		{ 0x222c, 0x00f5, 0xdb0e, 0xb017 }, { 0x2230, 0x0017, 0x48e2, 0xb017 },
		{ 0x2234, 0x00f5, 0xdb0e, 0xb017 }, { 0x2238, 0x00ef, 0x5ce2, 0xb017 },
		{ 0x223c, 0x00c1, 0xcc0d, 0xb017 }, { 0x2240, 0x00f5, 0xdb0e, 0xb017 },
		{ 0x2244, 0x0017, 0x48e2, 0xb017 }, { 0x2248, 0x00f5, 0xdb0e, 0xb017 },
		{ 0x224c, 0x00ef, 0x5ce2, 0xb017 }, { 0x2250, 0x00c1, 0xcc0d, 0xb017 },
		{ 0x2254, 0x00f5, 0xdb0e, 0xb017 }, { 0x2258, 0x0017, 0x48e2, 0xb017 },
		{ 0x225c, 0x00f5, 0xdb0e, 0xb017 }, { 0x2260, 0x00ef, 0x5ce2, 0xb017 },
		{ 0x2264, 0x00c1, 0xcc0d, 0xb017 }, { 0x2268, 0x00f5, 0xdb0e, 0xb017 },
		{ 0x226c, 0x0017, 0x48e2, 0xb017 }, { 0x2270, 0x00f5, 0xdb0e, 0xb017 },
		{ 0x2274, 0x00ef, 0x5ce2, 0xb017 }, { 0x2278, 0x00c1, 0xcc0d, 0xb017 },
		{ 0x227c, 0x00f5, 0xdb0e, 0xb017 }, { 0x2280, 0x0017, 0x48e2, 0xb017 },
		{ 0x2284, 0x00f5, 0xdb0e, 0xb017 }, { 0x2288, 0x00ef, 0x5ce2, 0xb017 },
		{ 0x228c, 0x00c1, 0xcc0d, 0xb017 }, { 0x22cc, 0x00e8, 0x8d00, 0xb017 },
		{ 0x22d0, 0x0000, 0x0000, 0xb017 }, { 0x22d4, 0x0018, 0x72ff, 0xb017 },
		{ 0x22d8, 0x00ce, 0x25e1, 0xb017 }, { 0x22dc, 0x002f, 0xe40e, 0xb017 },
		{ 0x238e, 0x0000, 0x0099, 0xb011 }, { 0x238f, 0x0000, 0x0011, 0xb011 },
		{ 0x2390, 0x0000, 0x0056, 0xb011 }, { 0x2391, 0x0000, 0x0004, 0xb011 },
		{ 0x2392, 0x0000, 0x00bb, 0xb011 }, { 0x2393, 0x0000, 0x006d, 0xb011 },
		{ 0x2394, 0x0000, 0x0010, 0xb011 }, { 0x2395, 0x0000, 0x0064, 0xb011 },
		{ 0x2396, 0x0000, 0x00b6, 0xb011 }, { 0x2397, 0x0000, 0x0028, 0xb011 },
		{ 0x2398, 0x0000, 0x000b, 0xb011 }, { 0x239a, 0x0000, 0x0099, 0xb011 },
		{ 0x239b, 0x0000, 0x000d, 0xb011 }, { 0x23a6, 0x0000, 0x0064, 0xb011 },
		{ 0x23a7, 0x0000, 0x0078, 0xb011 }, { 0x23b9, 0x0000, 0x0000, 0xb011 },
		{ 0x23e0, 0x0000, 0x0021, 0xb011 }, { 0x23e1, 0x0000, 0x0001, 0xb011 },
	};

	static const struct alc298_samsung_coeff_seq_desc amp_0x39[] = {
		{ 0x2000, 0x0000, 0x0001, 0xb011 }, { 0x23ff, 0x0000, 0x0000, 0xb011 },
		{ 0x203a, 0x0000, 0x0080, 0xb011 }, { 0x23e1, 0x0000, 0x0000, 0xb011 },
		{ 0x2012, 0x0000, 0x006f, 0xb011 }, { 0x2014, 0x0000, 0x0000, 0xb011 },
		{ 0x201b, 0x0000, 0x0002, 0xb011 }, { 0x201d, 0x0000, 0x0002, 0xb011 },
		{ 0x201f, 0x0000, 0x00fd, 0xb011 }, { 0x2021, 0x0000, 0x0001, 0xb011 },
		{ 0x2022, 0x0000, 0x0010, 0xb011 }, { 0x203d, 0x0000, 0x0005, 0xb011 },
		{ 0x203f, 0x0000, 0x0003, 0xb011 }, { 0x2050, 0x0000, 0x002c, 0xb011 },
		{ 0x2076, 0x0000, 0x000e, 0xb011 }, { 0x207c, 0x0000, 0x004a, 0xb011 },
		{ 0x2081, 0x0000, 0x0003, 0xb011 }, { 0x2399, 0x0000, 0x0003, 0xb011 },
		{ 0x23a4, 0x0000, 0x00b5, 0xb011 }, { 0x23a5, 0x0000, 0x0001, 0xb011 },
		{ 0x23ba, 0x0000, 0x0094, 0xb011 }, { 0x2100, 0x00d0, 0x950e, 0xb017 },
		{ 0x2104, 0x0061, 0xd4e2, 0xb017 }, { 0x2108, 0x00d0, 0x950e, 0xb017 },
		{ 0x210c, 0x0075, 0xf4e2, 0xb017 }, { 0x2110, 0x00b4, 0x4b0d, 0xb017 },
		{ 0x2114, 0x000a, 0x1000, 0xb017 }, { 0x2118, 0x0015, 0x2000, 0xb017 },
		{ 0x211c, 0x000a, 0x1000, 0xb017 }, { 0x2120, 0x0075, 0xf4e2, 0xb017 },
		{ 0x2124, 0x00b4, 0x4b0d, 0xb017 }, { 0x2128, 0x0000, 0x0010, 0xb017 },
		{ 0x212c, 0x0000, 0x0000, 0xb017 }, { 0x2130, 0x0000, 0x0000, 0xb017 },
		{ 0x2134, 0x0000, 0x0000, 0xb017 }, { 0x2138, 0x0000, 0x0000, 0xb017 },
		{ 0x213c, 0x0000, 0x0010, 0xb017 }, { 0x2140, 0x0000, 0x0000, 0xb017 },
		{ 0x2144, 0x0000, 0x0000, 0xb017 }, { 0x2148, 0x0000, 0x0000, 0xb017 },
		{ 0x214c, 0x0000, 0x0000, 0xb017 }, { 0x2150, 0x0000, 0x0010, 0xb017 },
		{ 0x2154, 0x0000, 0x0000, 0xb017 }, { 0x2158, 0x0000, 0x0000, 0xb017 },
		{ 0x215c, 0x0000, 0x0000, 0xb017 }, { 0x2160, 0x0000, 0x0000, 0xb017 },
		{ 0x2164, 0x0000, 0x0010, 0xb017 }, { 0x2168, 0x0000, 0x0000, 0xb017 },
		{ 0x216c, 0x0000, 0x0000, 0xb017 }, { 0x2170, 0x0000, 0x0000, 0xb017 },
		{ 0x2174, 0x0000, 0x0000, 0xb017 }, { 0x2178, 0x0000, 0x0010, 0xb017 },
		{ 0x217c, 0x0000, 0x0000, 0xb017 }, { 0x2180, 0x0000, 0x0000, 0xb017 },
		{ 0x2184, 0x0000, 0x0000, 0xb017 }, { 0x2188, 0x0000, 0x0000, 0xb017 },
		{ 0x218c, 0x0064, 0x5800, 0xb017 }, { 0x2190, 0x00c8, 0xb000, 0xb017 },
		{ 0x2194, 0x0064, 0x5800, 0xb017 }, { 0x2198, 0x003d, 0x5be7, 0xb017 },
		{ 0x219c, 0x0054, 0x060a, 0xb017 }, { 0x21a0, 0x00c8, 0xa310, 0xb017 },
		{ 0x21a4, 0x0029, 0x4de5, 0xb017 }, { 0x21a8, 0x0032, 0x420c, 0xb017 },
		{ 0x21ac, 0x0029, 0x4de5, 0xb017 }, { 0x21b0, 0x00fa, 0xe50c, 0xb017 },
		{ 0x21b4, 0x0000, 0x0010, 0xb017 }, { 0x21b8, 0x0000, 0x0000, 0xb017 },
		{ 0x21bc, 0x0000, 0x0000, 0xb017 }, { 0x21c0, 0x0000, 0x0000, 0xb017 },
		{ 0x21c4, 0x0000, 0x0000, 0xb017 }, { 0x21c8, 0x0056, 0xc50f, 0xb017 },
		{ 0x21cc, 0x007b, 0xd7e1, 0xb017 }, { 0x21d0, 0x0077, 0xa70e, 0xb017 },
		{ 0x21d4, 0x00e0, 0xbde1, 0xb017 }, { 0x21d8, 0x0032, 0x530e, 0xb017 },
		{ 0x2204, 0x00fb, 0x7e0f, 0xb017 }, { 0x2208, 0x000b, 0x02e1, 0xb017 },
		{ 0x220c, 0x00fb, 0x7e0f, 0xb017 }, { 0x2210, 0x00d5, 0x17e1, 0xb017 },
		{ 0x2214, 0x00c0, 0x130f, 0xb017 }, { 0x2218, 0x00e5, 0x0a00, 0xb017 },
		{ 0x221c, 0x00cb, 0x1500, 0xb017 }, { 0x2220, 0x00e5, 0x0a00, 0xb017 },
		{ 0x2224, 0x00d5, 0x17e1, 0xb017 }, { 0x2228, 0x00c0, 0x130f, 0xb017 },
		{ 0x222c, 0x00f5, 0xdb0e, 0xb017 }, { 0x2230, 0x0017, 0x48e2, 0xb017 },
		{ 0x2234, 0x00f5, 0xdb0e, 0xb017 }, { 0x2238, 0x00ef, 0x5ce2, 0xb017 },
		{ 0x223c, 0x00c1, 0xcc0d, 0xb017 }, { 0x2240, 0x00f5, 0xdb0e, 0xb017 },
		{ 0x2244, 0x0017, 0x48e2, 0xb017 }, { 0x2248, 0x00f5, 0xdb0e, 0xb017 },
		{ 0x224c, 0x00ef, 0x5ce2, 0xb017 }, { 0x2250, 0x00c1, 0xcc0d, 0xb017 },
		{ 0x2254, 0x00f5, 0xdb0e, 0xb017 }, { 0x2258, 0x0017, 0x48e2, 0xb017 },
		{ 0x225c, 0x00f5, 0xdb0e, 0xb017 }, { 0x2260, 0x00ef, 0x5ce2, 0xb017 },
		{ 0x2264, 0x00c1, 0xcc0d, 0xb017 }, { 0x2268, 0x00f5, 0xdb0e, 0xb017 },
		{ 0x226c, 0x0017, 0x48e2, 0xb017 }, { 0x2270, 0x00f5, 0xdb0e, 0xb017 },
		{ 0x2274, 0x00ef, 0x5ce2, 0xb017 }, { 0x2278, 0x00c1, 0xcc0d, 0xb017 },
		{ 0x227c, 0x00f5, 0xdb0e, 0xb017 }, { 0x2280, 0x0017, 0x48e2, 0xb017 },
		{ 0x2284, 0x00f5, 0xdb0e, 0xb017 }, { 0x2288, 0x00ef, 0x5ce2, 0xb017 },
		{ 0x228c, 0x00c1, 0xcc0d, 0xb017 }, { 0x22cc, 0x00e8, 0x8d00, 0xb017 },
		{ 0x22d0, 0x0000, 0x0000, 0xb017 }, { 0x22d4, 0x0018, 0x72ff, 0xb017 },
		{ 0x22d8, 0x00ce, 0x25e1, 0xb017 }, { 0x22dc, 0x002f, 0xe40e, 0xb017 },
		{ 0x238e, 0x0000, 0x0099, 0xb011 }, { 0x238f, 0x0000, 0x0011, 0xb011 },
		{ 0x2390, 0x0000, 0x0056, 0xb011 }, { 0x2391, 0x0000, 0x0004, 0xb011 },
		{ 0x2392, 0x0000, 0x00bb, 0xb011 }, { 0x2393, 0x0000, 0x006d, 0xb011 },
		{ 0x2394, 0x0000, 0x0010, 0xb011 }, { 0x2395, 0x0000, 0x0064, 0xb011 },
		{ 0x2396, 0x0000, 0x00b6, 0xb011 }, { 0x2397, 0x0000, 0x0028, 0xb011 },
		{ 0x2398, 0x0000, 0x000b, 0xb011 }, { 0x239a, 0x0000, 0x0099, 0xb011 },
		{ 0x239b, 0x0000, 0x000d, 0xb011 }, { 0x23a6, 0x0000, 0x0064, 0xb011 },
		{ 0x23a7, 0x0000, 0x0078, 0xb011 }, { 0x23b9, 0x0000, 0x0000, 0xb011 },
		{ 0x23e0, 0x0000, 0x0021, 0xb011 }, { 0x23e1, 0x0000, 0x0001, 0xb011 },
	};

	static const struct alc298_samsung_coeff_seq_desc amp_0x3c[] = {
		{ 0x2000, 0x0000, 0x0001, 0xb011 }, { 0x23ff, 0x0000, 0x0000, 0xb011 },
		{ 0x203a, 0x0000, 0x0080, 0xb011 }, { 0x23e1, 0x0000, 0x0000, 0xb011 },
		{ 0x2012, 0x0000, 0x006f, 0xb011 }, { 0x2014, 0x0000, 0x0000, 0xb011 },
		{ 0x201b, 0x0000, 0x0001, 0xb011 }, { 0x201d, 0x0000, 0x0001, 0xb011 },
		{ 0x201f, 0x0000, 0x00fe, 0xb011 }, { 0x2021, 0x0000, 0x0000, 0xb011 },
		{ 0x2022, 0x0000, 0x0010, 0xb011 }, { 0x203d, 0x0000, 0x0005, 0xb011 },
		{ 0x203f, 0x0000, 0x0003, 0xb011 }, { 0x2050, 0x0000, 0x002c, 0xb011 },
		{ 0x2076, 0x0000, 0x000e, 0xb011 }, { 0x207c, 0x0000, 0x004a, 0xb011 },
		{ 0x2081, 0x0000, 0x0003, 0xb011 }, { 0x23ba, 0x0000, 0x008d, 0xb011 },
		{ 0x2128, 0x0005, 0x460d, 0xb017 }, { 0x212c, 0x00f6, 0x73e5, 0xb017 },
		{ 0x2130, 0x0005, 0x460d, 0xb017 }, { 0x2134, 0x00c0, 0xe9e5, 0xb017 },
		{ 0x2138, 0x00d5, 0x010b, 0xb017 }, { 0x213c, 0x009d, 0x7809, 0xb017 },
		{ 0x2140, 0x00c5, 0x0eed, 0xb017 }, { 0x2144, 0x009d, 0x7809, 0xb017 },
		{ 0x2148, 0x00c4, 0x4ef0, 0xb017 }, { 0x214c, 0x003a, 0x3106, 0xb017 },
		{ 0x2150, 0x00af, 0x750e, 0xb017 }, { 0x2154, 0x008c, 0x1ff1, 0xb017 },
		{ 0x2158, 0x009e, 0x360c, 0xb017 }, { 0x215c, 0x008c, 0x1ff1, 0xb017 },
		{ 0x2160, 0x004d, 0xac0a, 0xb017 }, { 0x2164, 0x007d, 0xa00f, 0xb017 },
		{ 0x2168, 0x00e1, 0x9ce3, 0xb017 }, { 0x216c, 0x00e8, 0x590e, 0xb017 },
		{ 0x2170, 0x00e1, 0x9ce3, 0xb017 }, { 0x2174, 0x0066, 0xfa0d, 0xb017 },
		{ 0x2178, 0x0000, 0x0010, 0xb017 }, { 0x217c, 0x0000, 0x0000, 0xb017 },
		{ 0x2180, 0x0000, 0x0000, 0xb017 }, { 0x2184, 0x0000, 0x0000, 0xb017 },
		{ 0x2188, 0x0000, 0x0000, 0xb017 }, { 0x218c, 0x0000, 0x0010, 0xb017 },
		{ 0x2190, 0x0000, 0x0000, 0xb017 }, { 0x2194, 0x0000, 0x0000, 0xb017 },
		{ 0x2198, 0x0000, 0x0000, 0xb017 }, { 0x219c, 0x0000, 0x0000, 0xb017 },
		{ 0x21a0, 0x0000, 0x0010, 0xb017 }, { 0x21a4, 0x0000, 0x0000, 0xb017 },
		{ 0x21a8, 0x0000, 0x0000, 0xb017 }, { 0x21ac, 0x0000, 0x0000, 0xb017 },
		{ 0x21b0, 0x0000, 0x0000, 0xb017 }, { 0x21b4, 0x0000, 0x0010, 0xb017 },
		{ 0x21b8, 0x0000, 0x0000, 0xb017 }, { 0x21bc, 0x0000, 0x0000, 0xb017 },
		{ 0x21c0, 0x0000, 0x0000, 0xb017 }, { 0x21c4, 0x0000, 0x0000, 0xb017 },
		{ 0x23b9, 0x0000, 0x0000, 0xb011 }, { 0x23e0, 0x0000, 0x0020, 0xb011 },
		{ 0x23e1, 0x0000, 0x0001, 0xb011 },
	};

	static const struct alc298_samsung_coeff_seq_desc amp_0x3d[] = {
		{ 0x2000, 0x0000, 0x0001, 0xb011 }, { 0x23ff, 0x0000, 0x0000, 0xb011 },
		{ 0x203a, 0x0000, 0x0080, 0xb011 }, { 0x23e1, 0x0000, 0x0000, 0xb011 },
		{ 0x2012, 0x0000, 0x006f, 0xb011 }, { 0x2014, 0x0000, 0x0000, 0xb011 },
		{ 0x201b, 0x0000, 0x0002, 0xb011 }, { 0x201d, 0x0000, 0x0002, 0xb011 },
		{ 0x201f, 0x0000, 0x00fd, 0xb011 }, { 0x2021, 0x0000, 0x0001, 0xb011 },
		{ 0x2022, 0x0000, 0x0010, 0xb011 }, { 0x203d, 0x0000, 0x0005, 0xb011 },
		{ 0x203f, 0x0000, 0x0003, 0xb011 }, { 0x2050, 0x0000, 0x002c, 0xb011 },
		{ 0x2076, 0x0000, 0x000e, 0xb011 }, { 0x207c, 0x0000, 0x004a, 0xb011 },
		{ 0x2081, 0x0000, 0x0003, 0xb011 }, { 0x23ba, 0x0000, 0x008d, 0xb011 },
		{ 0x2128, 0x0005, 0x460d, 0xb017 }, { 0x212c, 0x00f6, 0x73e5, 0xb017 },
		{ 0x2130, 0x0005, 0x460d, 0xb017 }, { 0x2134, 0x00c0, 0xe9e5, 0xb017 },
		{ 0x2138, 0x00d5, 0x010b, 0xb017 }, { 0x213c, 0x009d, 0x7809, 0xb017 },
		{ 0x2140, 0x00c5, 0x0eed, 0xb017 }, { 0x2144, 0x009d, 0x7809, 0xb017 },
		{ 0x2148, 0x00c4, 0x4ef0, 0xb017 }, { 0x214c, 0x003a, 0x3106, 0xb017 },
		{ 0x2150, 0x00af, 0x750e, 0xb017 }, { 0x2154, 0x008c, 0x1ff1, 0xb017 },
		{ 0x2158, 0x009e, 0x360c, 0xb017 }, { 0x215c, 0x008c, 0x1ff1, 0xb017 },
		{ 0x2160, 0x004d, 0xac0a, 0xb017 }, { 0x2164, 0x007d, 0xa00f, 0xb017 },
		{ 0x2168, 0x00e1, 0x9ce3, 0xb017 }, { 0x216c, 0x00e8, 0x590e, 0xb017 },
		{ 0x2170, 0x00e1, 0x9ce3, 0xb017 }, { 0x2174, 0x0066, 0xfa0d, 0xb017 },
		{ 0x2178, 0x0000, 0x0010, 0xb017 }, { 0x217c, 0x0000, 0x0000, 0xb017 },
		{ 0x2180, 0x0000, 0x0000, 0xb017 }, { 0x2184, 0x0000, 0x0000, 0xb017 },
		{ 0x2188, 0x0000, 0x0000, 0xb017 }, { 0x218c, 0x0000, 0x0010, 0xb017 },
		{ 0x2190, 0x0000, 0x0000, 0xb017 }, { 0x2194, 0x0000, 0x0000, 0xb017 },
		{ 0x2198, 0x0000, 0x0000, 0xb017 }, { 0x219c, 0x0000, 0x0000, 0xb017 },
		{ 0x21a0, 0x0000, 0x0010, 0xb017 }, { 0x21a4, 0x0000, 0x0000, 0xb017 },
		{ 0x21a8, 0x0000, 0x0000, 0xb017 }, { 0x21ac, 0x0000, 0x0000, 0xb017 },
		{ 0x21b0, 0x0000, 0x0000, 0xb017 }, { 0x21b4, 0x0000, 0x0010, 0xb017 },
		{ 0x21b8, 0x0000, 0x0000, 0xb017 }, { 0x21bc, 0x0000, 0x0000, 0xb017 },
		{ 0x21c0, 0x0000, 0x0000, 0xb017 }, { 0x21c4, 0x0000, 0x0000, 0xb017 },
		{ 0x23b9, 0x0000, 0x0000, 0xb011 }, { 0x23e0, 0x0000, 0x0020, 0xb011 },
		{ 0x23e1, 0x0000, 0x0001, 0xb011 },
	};

	static const struct alc298_samsung_coeff_seq_desc amp_seq1[] = {
		{ 0x23ff, 0x0000, 0x0000, 0xb011 }, { 0x203a, 0x0000, 0x0080, 0xb011 },
	};

	static const struct alc298_samsung_coeff_fixup_desc fixups2[] = {
		{ 0x4f, 0xb029 }, { 0x05, 0x2be0 }, { 0x30, 0x2421 },
	};


	static const struct alc298_samsung_coeff_seq_desc amp_seq2[] = {
		{ 0x203a, 0x0000, 0x0081, 0xb011 }, { 0x23ff, 0x0000, 0x0001, 0xb011 },
	};

	if (action != HDA_FIXUP_ACT_INIT)
		return;

	// First set of fixups
	for (i = 0; i < ARRAY_SIZE(fixups1); i++)
		alc_write_coef_idx(codec, fixups1[i].coeff_idx, fixups1[i].coeff_value);

	// First set of writes
	alc298_samsung_write_coef_pack_seq(codec, 0x38, amp_0x38, ARRAY_SIZE(amp_0x38));
	alc298_samsung_write_coef_pack_seq(codec, 0x39, amp_0x39, ARRAY_SIZE(amp_0x39));
	alc298_samsung_write_coef_pack_seq(codec, 0x3c, amp_0x3c, ARRAY_SIZE(amp_0x3c));
	alc298_samsung_write_coef_pack_seq(codec, 0x3d, amp_0x3d, ARRAY_SIZE(amp_0x3d));

	// Second set of writes
	alc298_samsung_write_coef_pack_seq(codec, 0x38, amp_seq1, ARRAY_SIZE(amp_seq1));
	alc298_samsung_write_coef_pack_seq(codec, 0x39, amp_seq1, ARRAY_SIZE(amp_seq1));
	alc298_samsung_write_coef_pack_seq(codec, 0x3c, amp_seq1, ARRAY_SIZE(amp_seq1));
	alc298_samsung_write_coef_pack_seq(codec, 0x3d, amp_seq1, ARRAY_SIZE(amp_seq1));

	// Second set of fixups
	for (i = 0; i < ARRAY_SIZE(fixups2); i++)
		alc_write_coef_idx(codec, fixups2[i].coeff_idx, fixups2[i].coeff_value);

	// Third set of writes
	alc298_samsung_write_coef_pack_seq(codec, 0x38, amp_seq2, ARRAY_SIZE(amp_seq2));
	alc298_samsung_write_coef_pack_seq(codec, 0x39, amp_seq2, ARRAY_SIZE(amp_seq2));
	alc298_samsung_write_coef_pack_seq(codec, 0x3c, amp_seq2, ARRAY_SIZE(amp_seq2));
	alc298_samsung_write_coef_pack_seq(codec, 0x3d, amp_seq2, ARRAY_SIZE(amp_seq2));

	// Final fixup
	alc_write_coef_idx(codec, 0x10, 0x0F21);
}
