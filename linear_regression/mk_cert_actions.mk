$(SELF_SIGNED_CRT):
	openssl req -x509 -nodes -newkey rsa:2048 \
	-keyout $(SELF_SIGNED_KEY) \
	-out $(SELF_SIGNED_CRT) \
	-days 365 \
	-subj "/C=FI/ST=Uusimaa/L=Espoo/O=/OU=Hive/CN=n-puzzle"
	chmod 644 $(SELF_SIGNED_CRT)
	chmod +r $(SELF_SIGNED_KEY)
