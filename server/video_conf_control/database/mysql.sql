CREATE TABLE IF NOT EXISTS `terminal_connection` (
    `id` bigint(20) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT 'Primary key ID',
    `app_id` varchar(64) NOT NULL DEFAULT '' COMMENT 'app id',
    `conn_id` varchar(64) NOT NULL DEFAULT '' COMMENT 'connection id',
    `addr` varchar(32) NOT NULL DEFAULT '' COMMENT 'frontier ipv4 addr',
    `addr6` varchar(32) NOT NULL DEFAULT '' COMMENT 'frontier ipv6 addr',
    `state`tinyint(4) NOT NULL DEFAULT '-1' COMMENT '0 inactive 1 active',
    `device_id` varchar(128) NOT NULL DEFAULT '' COMMENT 'device id',
    `created_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT 'create time',
    `updated_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT 'update time',
    PRIMARY KEY (`id`),
    KEY `idx_conn_id` (`conn_id`),
    KEY `idx_device_id` (`device_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT'terminal connection information';

CREATE TABLE IF NOT EXISTS `conference_user` (
    `id` bigint(20) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT 'Primary key ID',
    `app_id` varchar(32) NOT NULL DEFAULT '' COMMENT 'app id',
    `user_id` varchar(32) BINARY NOT NULL DEFAULT '' COMMENT 'user id',
    `room_id` varchar(32) BINARY NOT NULL DEFAULT '' COMMENT 'room id',
    `device_id` varchar(128) NOT NULL DEFAULT '' COMMENT 'device id',
    `conn_id` varchar(64) NOT NULL DEFAULT '' COMMENT 'connection id',
    `state`tinyint(4) NOT NULL DEFAULT '1' COMMENT '0 inactive 1 active 2 reconnecting',
    `is_host` tinyint(1) NOT NULL DEFAULT '0' COMMENT 'host state',
    `is_mic_on` tinyint(1) NOT NULL DEFAULT '0' COMMENT 'mic state',
    `is_camera_on` tinyint(1) NOT NULL DEFAULT '0' COMMENT 'camera state',
    `is_sharing` tinyint(1) NOT NULL DEFAULT '0' COMMENT 'screen share state',
    `created_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT 'create time',
    `updated_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT 'update time',
    PRIMARY KEY (`id`),
    KEY `idx_conn_id` (`conn_id`),
    KEY `idx_room_id_user_id` (`room_id`, `user_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT'conference user information';

CREATE TABLE IF NOT EXISTS `conference_room` (
    `id` bigint(20) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT 'Primary key ID',
    `app_id` varchar(32) NOT NULL DEFAULT '' COMMENT 'app id',
    `room_id` varchar(32) BINARY NOT NULL DEFAULT '' COMMENT 'room id',
    `state` tinyint(4) NOT NULL DEFAULT '-1' COMMENT '0 inactive 1 active',
    `record` tinyint(1) NOT NULL DEFAULT '0' COMMENT 'record state',
    `created_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT 'create time',
    `updated_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT 'update time',
    PRIMARY KEY (`id`),
	UNIQUE KEY `uniq_room_id` (`room_id`)
)ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT'conference room information';

CREATE TABLE IF NOT EXISTS `conference_video_record` (
    `id` bigint(20) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT 'Primary key ID',
    `room_id` varchar(32) BINARY NOT NULL DEFAULT '' COMMENT 'room id',
    `app_id` varchar(32) NOT NULL DEFAULT '' COMMENT 'app id',
	`vid` varchar(128) NOT NULL DEFAULT '' COMMENT 'video id',
    `created_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT 'create time',
    `updated_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT 'update time',
    PRIMARY KEY (`id`),
    KEY `idx_room_id` (`room_id`)
)ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT'conference record information';
