#!/bin/bash

print_help()
{
    echo "Select option: "
    echo "    'help' or 'h' - show help (this message)"
    echo "    1             - turn LED on"
    echo "    2             - turn LED off"
    echo "    3             - show LED state"
    echo "    4             - set LED color to red"
    echo "    5             - set LED color to green"
    echo "    6             - set LED color to blue"
    echo "    7             - show LED color"
    echo "    8             - set LED rate"
    echo "    9             - show LED rate"
}

requests=("" "set-led-state on" "set-led-state off" "get-led-state" 
          "set-led-color red" "set-led-color green" "set-led-color blue" "get-led-color" 
          "set-led-rate"  "get-led-rate");

request_pipe=/tmp/led_control_request
response_pipe=/tmp/led_control_response

# flush response pipe
dd iflag=nonblock if=/tmp/led_control_response of=/dev/null &> /dev/null

# print start help message
print_help

# main loop
while read -p ">" line
do
    # empty line
    if [[ ! $line =~ [^[:space:]] ]]; then
        continue
    fi
    # help line
    if [[ "$line" == 'help' ]] || [[ "$line" == 'h' ]]; then
        print_help
        continue
    fi
    # exit line
    if [[ "$line" == 'exit' ]]; then
        break
    fi

    # regular case

    if [[ $((line)) != $line ]]; then
        echo "error: entered option is not a number"
        continue
    fi

    #if [[ $line -ge 1 -a $line -le 9 ]; then
    if [ $line -ge 1 ] && [ $line -le 9 ] ; then

        request=${requests[$line]}
        echo "$request"

        if [[ "$line" == '8' ]]; then
            echo "enter LED rate (0..5):"
            read -p ">>" rate
            # append LED rate
            request="$request $rate"
        fi

        # write request
        echo $request >$request_pipe
 
        # read response
        read -t 3 response <$response_pipe; 

        # parse response
        response_words=($response)
        length=${#response_words[@]}

        if [ $length -ne 1 ] && [ $length -ne 2 ]; then
            echo "error: bad server response '$response'"
            continue
        fi

        if [[ ${response_words[0]} == "OK" ]]; then
            echo "request successfully processed"
        elif [[ ${response_words[0]} == "FAILED" ]]; then
            echo "request failed"
        else
            echo "error: bad server error code ${response_words[0]}"
            continue
        fi

        if [ $length -eq 2 ]; then
            echo "value: ${response_words[1]}"
        fi

    else
        echo "bad choice: only 1..9 allowed"
    fi
done
