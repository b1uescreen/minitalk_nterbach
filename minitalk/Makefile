COMPILE := cc -Wall -Werror -Wextra
CLIENT := client
SERVER := server
SOURCES_CL := minitalk_client.c 
SOURCES_SV := minitalk_srvr.c ft_printf/ft_printf_cnv_u.c \
				ft_printf/ft_printf_cnvrsn.c ft_printf/ft_printf_utils.c \
				ft_printf/ft_printf.c ft_printf/nt_itoa.c

all : $(CLIENT) $(SERVER)

$(CLIENT) : $(SOURCES_CL)
	$(COMPILE) $(SOURCES_CL) -o $(CLIENT)

$(SERVER) : $(SOURCES_SV)
	$(COMPILE) $(SOURCES_SV) -o $(SERVER)

clean :
	rm -f $(CLIENT)
	rm -f $(SERVER)

fclean : clean


re : fclean
	$(MAKE) all

.PHONY : all clean fclean re
