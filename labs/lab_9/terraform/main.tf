terraform {
  required_providers {
    twc = {
      source = "tf.timeweb.cloud/timeweb-cloud/timeweb-cloud"
    }
  }
  required_version = ">= 0.14"
}

variable "token" {
  type        = string
  description = "Token for timeweb"
}

provider "twc" {
  token = var.token
}


resource "twc_project" "lab9" {
  name        = "Lab 9 security moment"
  description = "Lab 9 project for security moment"
}

data "twc_os" "os" {
  name    = "ubuntu"
  version = "22.04"
}

data "twc_presets" "preset" {
  price_filter {
    from = 1200
    to   = 2400
  }
}

data "twc_ssh_keys" "ssh_key" {
  name = "lexxv@lexxv-work-sec-moment"
}

resource "twc_server" "server_1" {
  name  = "server"
  os_id = data.twc_os.os.id

  preset_id = data.twc_presets.preset.id

  project_id = resource.twc_project.lab9.id

  ssh_keys_ids = [data.twc_ssh_keys.ssh_key.id]
}

resource "twc_server_ip" "ip_1" {
  source_server_id = twc_server.server_1.id

  type = "ipv4"

  ptr = format("mail.attacker.%s", data.twc_dns_zone.dnz_zone.name)
}

output "ipv4_1" {
  value = twc_server_ip.ip_1.ip
}

resource "twc_server" "server_2" {
  name  = "server"
  os_id = data.twc_os.os.id

  preset_id = data.twc_presets.preset.id

  project_id = resource.twc_project.lab9.id

  ssh_keys_ids = [data.twc_ssh_keys.ssh_key.id]
}

resource "twc_server_ip" "ip_2" {
  source_server_id = twc_server.server_2.id

  type = "ipv4"

  ptr = format("mail.defender.%s", data.twc_dns_zone.dnz_zone_2.name)
}

output "ipv4_2" {
  value = twc_server_ip.ip_2.ip
}

data "twc_dns_zone" "dnz_zone" {
  name = "lab9.tw1.ru"
}


resource "twc_dns_rr" "attacker-record" {
  zone_id = data.twc_dns_zone.dnz_zone.id

  name  = "attacker"
  type  = "A"
  value = twc_server_ip.ip_1.ip
}

resource "twc_dns_rr" "mail-attacker-record" {
  zone_id = data.twc_dns_zone.dnz_zone.id

  name  = "mail.attacker"
  type  = "A"
  value = twc_server_ip.ip_1.ip
}

resource "twc_dns_rr" "mail-attacker-record-autodiscover" {
  zone_id = data.twc_dns_zone.dnz_zone.id

  name = "autodiscover"
  type = "CNAME"
  value = format("mail.attacker.%s", data.twc_dns_zone.dnz_zone.name)
}

resource "twc_dns_rr" "mail-attacker-record-autoconfig" {
  zone_id = data.twc_dns_zone.dnz_zone.id

  name = "autoconfig"
  type = "CNAME"
  value = format("mail.attacker.%s", data.twc_dns_zone.dnz_zone.name)
}

resource "twc_dns_rr" "mail-attacker-record-mx" {
  zone_id = data.twc_dns_zone.dnz_zone.id

  name = "@"
  type = "MX"
  value = format("10 mail.attacker.%s", data.twc_dns_zone.dnz_zone.name)
}

data "twc_dns_zone" "dnz_zone_2" {
  name = "lab9-2.tw1.ru"
}

resource "twc_dns_rr" "defender-record" {
  zone_id = data.twc_dns_zone.dnz_zone_2.id

  name  = "defender"
  type  = "A"
  value = twc_server_ip.ip_2.ip
}

resource "twc_dns_rr" "mail-defender-record" {
  zone_id = data.twc_dns_zone.dnz_zone_2.id

  name  = "mail.defender"
  type  = "A"
  value = twc_server_ip.ip_2.ip
}

resource "twc_dns_rr" "mail-defender-record-autodiscover" {
  zone_id = data.twc_dns_zone.dnz_zone_2.id

  name = "autodiscover"
  type = "CNAME"
  value = format("mail.defender.%s", data.twc_dns_zone.dnz_zone_2.name)
}

resource "twc_dns_rr" "mail-defender-record-autoconfig" {
  zone_id = data.twc_dns_zone.dnz_zone_2.id

  name = "autoconfig"
  type = "CNAME"
  value = format("mail.defender.%s", data.twc_dns_zone.dnz_zone_2.name)
}

resource "twc_dns_rr" "mail-defender-record-mx" {
  zone_id = data.twc_dns_zone.dnz_zone_2.id

  name = "@"
  type = "MX"
  value = format("10 mail.defender.%s", data.twc_dns_zone.dnz_zone_2.name)
}
