#ZEAMAP Genotype Instruction
##prerequisite
- htslib (git://github.com/samtools/htslib.git)
- bcftools (git://github.com/samtools/bcftools.git)
## install
- 安装以上两个工具，并将bcftools添加到环境变量
- 在sites/default/files/zmap_genotype 目录下 建立sample lists文件的软链接
- 启用模块 drush en -y zmap_genotype
