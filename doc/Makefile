NAME = pia

default : all

all : $(NAME).3 $(NAME).txt

XSL_BASE  = http://docbook.sourceforge.net/release/xsl/current
MAN_XSL   = $(XSL_BASE)/manpages/docbook.xsl
XHTML_XSL = $(XSL_BASE)/xhtml/docbook.xsl

$(NAME).3 : $(NAME).xml
	xsltproc --xinclude $(MAN_XSL) $(NAME).xml > $(NAME).3

$(NAME).txt : $(NAME).xml
	xsltproc --xinclude $(XHTML_XSL) $(NAME).xml | \
	  lynx -stdin -dump -nolist > $(NAME).txt

clean :
