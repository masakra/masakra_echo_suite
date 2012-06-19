%% -*- erlang-indent-level: 4;indent-tabs-mode: nil -*-
%% ex: ts=4 sw=4 et
%% @author {{author}} <{{author_email}}>
%% @copyright {{copyright_year}} {{copyright_holder}}

-module(echoserver).

-behaviour(gen_server).

-export([start_link/0]).

%% gen_server callbacks
-export([init/1,
         handle_call/3,
         handle_cast/2,
         handle_info/2,
         terminate/2,
         code_change/3]).

-record(state, {}).

-define( TCP_OPTIONS, [binary, {packet, 0}, {active, false}, {reuseaddr, true}] ).

start_link() ->
    gen_server:start_link({local, ?MODULE}, ?MODULE, [], []).

init([]) ->
    {ok, LSocket} = gen_tcp:listen( 7000, ?TCP_OPTIONS ),
    accept( LSocket ).
    %%{ok, #state{}}.

handle_call(_Request, _From, State) ->
    io:format("Hello from gen_server, echo will.....~n", []),
    {reply, ok, State}.

handle_cast(_Msg, State) ->
    {noreply, State}.

handle_info(_Info, State) ->
    {noreply, State}.

terminate(_Reason, _State) ->
    ok.

code_change(_OldVsn, State, _Extra) ->
    {ok, State}.

%% Internal functions

accept( LSocket ) ->
    {ok, Socket} = gen_tcp:accept( LSocket ),
    spawn( fun() -> loop( Socket ) end ),
    accept( LSocket ).

loop( Socket ) ->
    case gen_tcp:recv( Socket, 0 ) of
        {ok, Data} ->
            gen_tcp:send( Socket, Data ),
            loop( Socket );
        {error, closed} ->
            ok
    end.

