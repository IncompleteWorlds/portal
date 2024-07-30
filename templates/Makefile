# 
#  (c) Incomplete Worlds July 2024
#  Alberto Fernandez
# 
# Your own Portal to your Internet
# 
#

ifndef PAGE_COMPILER
   ifdef POCO_BASE
       PAGE_COMPILER=${POCO_BASE}/bin/cpspc
   else
   	   PAGE_COMPILER=/home/alberto/Documents/poco-install/bin/cpspc
   endif
endif

# Rule for runnning PageCompiler
%.cpp: %.cpsp
	@echo "** Compiling Page" $<
	$(PAGE_COMPILER) $< -o $(ODIR)

ODIR=./output

TEMPL=index.cpp

pages: $(TEMPL)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.h $(ODIR)/*.cpp