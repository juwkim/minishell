#/bin/bash

TARGET=(
  "Caches"
  "ApplicationSupport/Code/Cache"
  "ApplicationSupport/Code/CachedData"
  "ApplicationSupport/Code/CachedExtensions"
  "ApplicationSupport/Code/CachedExtensionVSIXs"
  "ApplicationSupport/Code/Code Cache"
  "ApplicationSupport/Slack/Cache"
  "ApplicationSupport/Slack/CachedData"
  "ApplicationSupport/Slack/Service Worker/CacheStorage"
  "ApplicationSupport/Slack/Service Worker/ScriptCache"
)

FLAG="$HOME/goinfre/issetup"
function link_all_cache_dirs() {
  echo "link Code Slack Cache dirs..."
  for ((i = 0; i < ${#TARGET[@]}; i++)); do
    mkdir -p "$HOME/goinfre/${TARGET[$i]}"
    rm -rf "$HOME/Library/${TARGET[$i]}"
    ln -s "$HOME/goinfre/${TARGET[$i]}" "$HOME/Library/${TARGET[$i]}"
  done
  echo "Complete link all Cache dirs!"
  touch "$FLAG"
}

if [ ! -e "$FLAG" ]; then
  echo "$BANNER"
  link_all_cache_dirs
fi