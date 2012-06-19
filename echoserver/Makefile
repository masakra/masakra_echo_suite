
ERL=/usr/local/bin/erl
REBAR=/home/masakra/bin/rebar
VIM=/usr/local/bin/vim

build:
	${REBAR} compile

node:
	mkdir -p rel && cd rel && ${REBAR} create-node nodeid=echoserver

clean:
	rm -rf rel/*

gen:
	${REBAR} generate

edit:
	${VIM} rel/reltool.config


