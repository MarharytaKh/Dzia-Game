import argparse
import os
import platform
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent


def run(cmd):
    print("+ " + " ".join(str(c) for c in cmd), flush=True)
    subprocess.run([str(c) for c in cmd], cwd=ROOT, check=True)


def git_version():
    try:
        tag = subprocess.run(
            ["git", "describe", "--tags", "--match", "v*", "--dirty"],
            cwd=ROOT, capture_output=True, text=True, check=True,
        ).stdout.strip()
        return tag[1:] if tag.startswith("v") else tag
    except subprocess.CalledProcessError:
        sha = subprocess.run(
            ["git", "rev-parse", "--short", "HEAD"],
            cwd=ROOT, capture_output=True, text=True, check=True,
        ).stdout.strip()
        return "0.0.0-" + sha


def platform_name():
    system = platform.system().lower()
    machine = platform.machine().lower()
    machine = {"amd64": "x64", "x86_64": "x64", "aarch64": "arm64"}.get(machine, machine)
    return system + "-" + machine


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--build-dir", default="build")
    parser.add_argument("--dist-dir", default="dist")
    parser.add_argument("--config", default="Release")
    parser.add_argument("--generator")
    parser.add_argument("--toolset")
    parser.add_argument("--skip-tests", action="store_true")
    args = parser.parse_args()

    build_dir = ROOT / args.build_dir
    dist_dir = ROOT / args.dist_dir
    version = git_version()
    package_name = "DziaGame-" + version + "-" + platform_name()
    stage_dir = build_dir / "stage" / package_name

    configure = ["cmake", "-S", ROOT, "-B", build_dir, "-DCMAKE_BUILD_TYPE=" + args.config]
    if args.generator:
        configure += ["-G", args.generator]
    if args.toolset:
        configure += ["-T", args.toolset]
    run(configure)
    run(["cmake", "--build", build_dir, "--config", args.config, "--parallel"])

    if not args.skip_tests:
        run(["ctest", "--test-dir", build_dir, "-C", args.config, "--output-on-failure"])

    if stage_dir.exists():
        shutil.rmtree(stage_dir)
    run(["cmake", "--install", build_dir, "--config", args.config, "--prefix", stage_dir])

    dist_dir.mkdir(parents=True, exist_ok=True)
    archive = shutil.make_archive(str(dist_dir / package_name), "zip", stage_dir.parent, package_name)
    print("Release: " + archive)

    github_output = os.environ.get("GITHUB_OUTPUT")
    if github_output:
        with open(github_output, "a", encoding="utf-8") as f:
            f.write("archive=" + archive + "\n")
            f.write("version=" + version + "\n")


if __name__ == "__main__":
    try:
        main()
    except subprocess.CalledProcessError as e:
        sys.exit(e.returncode)
