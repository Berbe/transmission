// This file Copyright © 2022-2023 Mnemosyne LLC.
// It may be used under GPLv2 (SPDX: GPL-2.0-only), GPLv3 (SPDX: GPL-3.0-only),
// or any future license endorsed by Mnemosyne LLC.
// License text can be found in the licenses/ folder.

#include <fmt/format.h>

#include "transmission.h"

#include "session-settings.h"
#include "variant.h"

void tr_session_settings::load(tr_variant* src)
{
#define V(key, field, type, default_value, comment) \
    if (auto* const child = tr_variantDictFind(src, key); child != nullptr) \
    { \
        if (auto val = libtransmission::VariantConverter::load<decltype(field)>(child); val) \
        { \
            this->field = *val; \
        } \
    }
    SESSION_SETTINGS_FIELDS(V)
#undef V
}

void tr_session_settings::save(tr_variant* tgt) const
{
#define V(key, field, type, default_value, comment) \
    tr_variantDictRemove(tgt, key); \
    libtransmission::VariantConverter::save<decltype(field)>(tr_variantDictAdd(tgt, key), field);
    SESSION_SETTINGS_FIELDS(V)
#undef V
}

void tr_session_settings::save(::transmission::Settings& settings) const
{
    settings.set("announce_ip", (std::string) "", "");
    settings.set("announce_ip_enabled", (bool)false, "");
    settings.set("bind_address_ipv4", (std::string) "0.0.0.0", "");
    settings.set("bind_address_ipv6", (std::string) "::", "");
    settings.set("blocklist_enabled", (bool)false, "");
    settings.set("blocklist_url", (std::string) "http://www.example.com/blocklist", "");
    settings.set("cache_size_mb", (size_t)4U, "");
    settings.set("default_trackers_str", (std::string) "", "");
    settings.set("dht_enabled", (bool)true, "");
    settings.set("download_dir", (std::string)tr_getDefaultDownloadDir(), "");
    settings.set("download_queue_enabled", (bool)true, "");
    settings.set("download_queue_size", (size_t)5U, "");
    //settings.set("encryption_mode", (tr_encryption_mode)TR_ENCRYPTION_PREFERRED, "");
    settings.set("idle_seeding_limit_minutes", (size_t)30U, "");
    settings.set("idle_seeding_limit_enabled", (bool)false, "");
    settings.set("incomplete_dir", (std::string)tr_getDefaultDownloadDir(), "");
    settings.set("incomplete_dir_enabled", (bool)false, "");
    settings.set("lpd_enabled", (bool)true, "");
    //settings.set("log_level", (tr_log_level)TR_LOG_INFO, "");
    settings.set("peer_congestion_algorithm", (std::string) "", "");
    settings.set("peer_limit_global", (size_t)TR_DEFAULT_PEER_LIMIT_GLOBAL, "");
    settings.set("peer_limit_per_torrent", (size_t)TR_DEFAULT_PEER_LIMIT_TORRENT, "");
    /*settings.set("peer_port", (tr_port)tr_port::fromHost(TR_DEFAULT_PEER_PORT), "The local machine's incoming peer port");
  settings.set("peer_port_random_high", (tr_port)tr_port::fromHost(65535), "");
  settings.set("peer_port_random_low", (tr_port)tr_port::fromHost(49152), "");*/
    settings.set("peer_port_random_on_start", (bool)false, "");
    //settings.set("peer_socket_tos", (tr_tos_t)0x04, "");
    settings.set("pex_enabled", (bool)true, "");
    settings.set("port_forwarding_enabled", (bool)true, "");
    //settings.set("preallocation_mode", (tr_preallocation_mode)TR_PREALLOCATE_SPARSE, "");
    settings.set("is_prefetch_enabled", (bool)true, "");
    settings.set("queue_stalled_enabled", (bool)true, "");
    settings.set("queue_stalled_minutes", (size_t)30U, "");
    settings.set("ratio_limit", (double)2.0, "");
    settings.set("ratio_limit_enabled", (bool)false, "");
    settings.set("is_incomplete_file_naming_enabled", (bool)false, "");
    settings.set("should_scrape_paused_torrents", (bool)true, "");
    settings.set("script_torrent_added_enabled", (bool)false, "");
    settings.set("script_torrent_added_filename", (std::string) "", "");
    settings.set("script_torrent_done_enabled", (bool)false, "");
    settings.set("script_torrent_done_filename", (std::string) "", "");
    settings.set("script_torrent_done_seeding_enabled", (bool)false, "");
    settings.set("script_torrent_done_seeding_filename", (std::string) "", "");
    settings.set("seed_queue_enabled", (bool)false, "");
    settings.set("seed_queue_size", (size_t)10U, "");
    settings.set("speed_limit_down", (size_t)100U, "");
    settings.set("speed_limit_down_enabled", (bool)false, "");
    settings.set("speed_limit_up", (size_t)100U, "");
    settings.set("speed_limit_up_enabled", (bool)false, "");
    settings.set("should_start_added_torrents", (bool)true, "");
    settings.set("tcp_enabled", (bool)true, "");
    settings.set("should_delete_source_torrents", (bool)false, "");
    //settings.set("umask", (tr_mode_t)022, "");
    settings.set("upload_slots_per_torrent", (size_t)8U, "");
    settings.set("utp_enabled", (bool)true, "");
    //settings.set("torrent_added_verify_mode", (tr_verify_added_mode)TR_VERIFY_ADDED_FAST, "");
}
